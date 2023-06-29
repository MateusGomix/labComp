/* ideia para controlar os registradores em uso:
 * liberar os registradores das atribuições, das menções de vetores,
 * das chamadas de função e parametros
 */

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"
#include "string.h"
#include "stdlib.h"

#define STRING_TAM 10
#define INT_MEM_BYTES 32

int isRegUsed[TOTAL_REGS] = {0};

Quad *raizLista = NULL;
Endereco *globalAux1 = NULL;
Endereco *globalAux2 = NULL;
int tempRegsCount = 0;
int labelsCount = 0;

Endereco *criaEnd(TipoEnd tipo, char *nome, int val)
{
   Endereco *newEnd = (Endereco *)malloc(sizeof(Endereco));

   newEnd->tipo = tipo;

   if (tipo == String)
      newEnd->conteudo.nome = nome;
   else
      newEnd->conteudo.val = val;
   newEnd->regPos = -1;
   return newEnd;
}

int buscaRegLivre(){
   int i;
   for(i = 0; i < TOTAL_REGS; i++)
      if(!isRegUsed[i]) {
         isRegUsed[i] = 1;
         return i;
      }
}

/* ideia para controlar os registradores em uso: vetor de registradores de 0s e 1s
 * onde um registrador e liberado sempre que uma OpK acabar
 */
Endereco *novoTemp(){
   char *regName = malloc(STRING_TAM);

   int regVal = buscaRegLivre();

   sprintf(regName, "t_%d", regVal);
   //snprintf(regName, sizeof(regName), "t_%d", tempRegsCount++);

   //printf("NUMERO DO REG: %d %s\n", regVal, regName);
   Endereco *returnReg = criaEnd(String, regName, -1);
   //printEnd(returnReg);
   returnReg->regPos = regVal;
   return returnReg;
}

Endereco *novoLabel(){
   char *labelName = malloc(STRING_TAM);
   int labelAux = labelsCount;

   sprintf(labelName, "L%d", labelsCount++);
   //snprintf(regName, sizeof(labelName), "t_%d", labelsCount++);

   //printf("NUMERO DO REG: %d %s\n", labelsCount, labelName);
   Endereco *returnReg = criaEnd(String, labelName, -1);
   returnReg->label = labelAux;
   //printEnd(returnReg);
   return returnReg;
}

Quad insereQuad(Operacao op, Endereco *end1, Endereco *end2, Endereco *end3)
{
   Quad *newNode = (Quad *)malloc(sizeof(Quad));
   newNode->op = op;
   newNode->end1 = end1;
   newNode->end2 = end2;
   newNode->end3 = end3;
   newNode->next = NULL;

   for (int i = 0; i < TOTAL_REGS; i++){
      newNode->regsUsados[i] = isRegUsed[i];
   }

   if (raizLista == NULL)
      raizLista = newNode;
   else
   {
      Quad *auxNode = raizLista;
      while (auxNode->next != NULL)
         auxNode = auxNode->next;

      auxNode->next = newNode;
   }

   //printf("entrou no if abaixo");
   /* Liberando espaço do vetor de regs ERRO AQUI*/
   if (end1 != NULL && (op == ret || op == iffalse)){
      int tempReg1 = end1->regPos;
      if(tempReg1 >= 0 && isRegUsed[tempReg1]) isRegUsed[tempReg1] = 0;
   }
   if (end2 != NULL){
      int tempReg2 = end2->regPos;
      if(tempReg2 >= 0 && isRegUsed[tempReg2]) isRegUsed[tempReg2] = 0;
   }
   //printf("saiu do if acima");
   if (end3 != NULL){
      int tempReg3 = end3->regPos;
      if(tempReg3 >= 0 && isRegUsed[tempReg3]) isRegUsed[tempReg3] = 0;
   }
   //printQuads();
}

/* tmpOffset is the memory offset for temps
   It is decremented each time a temp is
   stored, and incremeted when loaded again
*/
static int tmpOffset = 0;

/* prototype for internal recursive code generator */
void cGen(TreeNode *tree, TreeNode *parent);

/* Procedure genStmt generates code at a statement node */
static void genStmt(TreeNode *tree)
{
   Endereco *endAux1 = NULL, *endAux2 = NULL, *endAux3 = NULL;

   switch (tree->kind.stmt)
   {
   case RetornoK:
      if(tree->child[0] != NULL){
         cGen(tree->child[0], tree);
         endAux1 = globalAux1;
      }
      insereQuad(ret, endAux1, endAux2, endAux3);
      /*
      if (endAux1 != NULL){
         int tempReg1 = endAux1->regPos;
         //printf("%d", tempReg1);
         //printf("%d", isRegUsed[tempReg1]);
         
         if(tempReg1 >= 0 && isRegUsed[tempReg1]) isRegUsed[tempReg1] = 0;

         //printf("saiu do if do retornok");
      }*/

      break; /* RetornoK */
   case WhileK:
      {Endereco *labelWhileStart = novoLabel(), *labelWhileEnd = novoLabel();
      endAux1 = labelWhileStart;
      insereQuad(lab, endAux1, endAux2, endAux3);
      cGen(tree->child[0], tree);
      endAux1 = globalAux1;
      endAux2 = labelWhileEnd;
      insereQuad(iffalse, endAux1, endAux2, endAux3);
      cGen(tree->child[1], tree);
      endAux1 = labelWhileStart;
      endAux2 = NULL;
      insereQuad(gotolab, endAux1, endAux2, endAux3);
      endAux1 = labelWhileEnd;
      insereQuad(lab, endAux1, endAux2, endAux3);
      break; /* WhileK */}
   case IfK:
      if(tree->child[1] != NULL){
         Endereco *labelElseStart = novoLabel(), *labelElseEnd = novoLabel();
         cGen(tree->child[0], tree);
         endAux1 = globalAux1;
         endAux2 = labelElseStart;
         insereQuad(iffalse, endAux1, endAux2, endAux3);
         cGen(tree->child[1], tree);
         if(tree->child[2] != NULL){
            endAux1 = labelElseEnd;
            endAux2 = NULL;
            insereQuad(gotolab, endAux1, endAux2, endAux3);         
         }
         endAux1 = labelElseStart;
         endAux2 = NULL;
         insereQuad(lab, endAux1, endAux2, endAux3);
         if(tree->child[2] != NULL){
            cGen(tree->child[2], tree);
            endAux1 = labelElseEnd;
            insereQuad(lab, endAux1, endAux2, endAux3);
         }
      }
      
      break; /* IfK*/
   case RecebeK:
      endAux1 = criaEnd(String, tree->child[0]->attr.name, -1);
      //printf("aqui");
      cGen(tree->child[1], tree);
      //printf("aqui");
      endAux2 = globalAux1;
      endAux3 = globalAux2;
      if(tree->child[0]->vetor){
         cGen(tree->child[0]->child[0], tree->child[0]);
         Endereco *tempIndex = novoTemp();
         insereQuad(mult, tempIndex, globalAux1, criaEnd(Const, NULL, INT_MEM_BYTES));
         endAux3 = endAux2;
         endAux2 = tempIndex;
      }
      //printf("aqui");
      insereQuad(store, endAux1, endAux2, endAux3);
      //printf("aqui");

      /*int tempReg1 = endAux2->regPos;
      if(tempReg1 >= 0 && isRegUsed[tempReg1]) isRegUsed[tempReg1] = 0;
      if (endAux3 != NULL){
         int tempReg2 = endAux3->regPos;
         if(tempReg2 >= 0 && isRegUsed[tempReg2]) isRegUsed[tempReg2] = 0;
      }*/

      break; /* RecebeK */
   }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp(TreeNode *tree, TreeNode *parent)
{
   Endereco *endAux1 = NULL, *endAux2 = NULL, *endAux3 = NULL;
   switch (tree->kind.exp)
   {
   case OpK:
      //printf("entrou no opk\n");
      cGen(tree->child[0], tree);
      //printf("opk\n");
      endAux2 = globalAux1;
      cGen(tree->child[1], tree);
      //printf("opk\n");
      endAux3 = globalAux1;
      endAux1 = novoTemp();
      //printEnd(endAux1);
      //if(endAux1->tipo == String) printf("ELE TEM TIPO");
      //printf("opk\n");
      //cria temporario
      //converte tipo
      Operacao opAux;
      switch (tree->attr.op)
      {
      case SOMA:
         opAux = add;
         break;
      case SUB:
         opAux = sub;
         break;
      case MULT:
         opAux = mult;
         break;
      case DIV:
         opAux = divOp;
         break;
      case MENOR:
         opAux = lt;
         break;
      case MENORIG:
         opAux = lte;
         break;
      case MAIOR:
         opAux = gt;
         break;
      case MAIORIG:
         opAux = gte;
         break;
      case IGUAL:
         opAux = eq;
         break;   
      default:
         break;
      }
      //printf("opk\n");
      //printf("ENDEREÇO DO REG TEMPORARIO:");
      //printEnd(endAux1);
      insereQuad(opAux, endAux1, endAux2, endAux3);
      /*int tempReg1 = endAux2->regPos;
      if(tempReg1 >= 0 && isRegUsed[tempReg1]) isRegUsed[tempReg1] = 0;
      if (endAux3 != NULL){
         int tempReg2 = endAux3->regPos;
         if(tempReg2 >= 0 && isRegUsed[tempReg2]) isRegUsed[tempReg2] = 0;
      }*/
      /* ideia para controlar os registradores em uso: liberar os registradores temporarios 
       * endAux2 e endAux3 se forem regs temps
       */
      globalAux1 = endAux1;
      globalAux2 = NULL;
      //printf("opk\n");

      break; /* OpK */

   case ConstK:
      //printf("entrou no constk\n");
      globalAux1 = criaEnd(Const, NULL, tree->attr.val);
      //printf("constk\n");
      globalAux2 = NULL;
      break; /* ConstK */

   case IdK:
      // ativacao de funcao
      if (!strcmp(tree->tipoID, "fun"))
      {
         /* FALTANDO E/OU DANDO ERRADO */
         if(tree->qtdArgumentos > 0){
            for(TreeNode *aux = tree->child[0]; aux != NULL; aux = aux->sibling){
               genExp(aux, tree);
               endAux1 = globalAux1;
               insereQuad(param, endAux1, endAux2, endAux3);
            }
            /*for(int qtdArgsAux = tree->qtdArgumentos; qtdArgsAux > 0; qtdArgsAux--){
               TreeNode *aux = tree->child[0];
               for(int subAux = 1; subAux < qtdArgsAux && aux != NULL; aux = aux->sibling, subAux++);
               //printf("saiu do lacoooooo");
               genExp(aux, tree);
               endAux1 = globalAux1;
               insereQuad(param, endAux1, endAux2, endAux3);
            }*/
         }
         endAux1 = novoTemp();
         endAux2 = criaEnd(String, tree->attr.name, -1);
         endAux3 = criaEnd(Const, NULL, tree->qtdArgumentos);
         insereQuad(call, endAux1, endAux2, endAux3);
         globalAux1 = endAux1;
      }
      // declaracao ou mencao de variavel
      else
      {
         // declaracao
         if (tree->declaracao)
         {
            // printQuads();
            //printf("b");
            endAux1 = criaEnd(String, tree->attr.name, -1);
            endAux2 = criaEnd(String, tree->escopo, -1);
            endAux3 = NULL;
            // tamanho do vetor
            if (tree->vetor && !tree->isArg)
            {
               //printf("vetor");
               endAux3 = endAux2;
               endAux2 = criaEnd(Const, NULL, tree->child[0]->attr.val);
            }
            //printf("b");
            if(!tree->isArg) insereQuad(aloc, endAux1, endAux2, endAux3);
            else {
               if(parent->sibling != NULL) genExp(parent->sibling->child[0], parent->sibling);
               insereQuad(arg, endAux1, endAux2, endAux3);
            }
            //printf("b");
         }
         // mencao
         else
         {
            // nao vetor
            if(!tree->vetor){
               endAux1 = novoTemp();
               endAux2 = criaEnd(String, tree->attr.name, -1);
               insereQuad(load, endAux1, endAux2, endAux3);
               globalAux1 = endAux1;
               globalAux2 = NULL;
            }
            // vetor
            else{
               if(tree->child[0] != NULL){
                  cGen(tree->child[0], tree);
                  Endereco *vetIndex = globalAux1;
                  endAux1 = novoTemp();
                  endAux2 = vetIndex;
                  endAux3 = criaEnd(Const, NULL, INT_MEM_BYTES);
                  insereQuad(mult, endAux1, endAux2, endAux3);

                  //int tempReg1 = endAux2->regPos;
                  //if(tempReg1 >= 0 && isRegUsed[tempReg1]) isRegUsed[tempReg1] = 0;

                  endAux3 = endAux1;
               }
               endAux1 = novoTemp();
               endAux2 = criaEnd(String, tree->attr.name, -1);
               
               insereQuad(load, endAux1, endAux2, endAux3);

               //if(tempReg1 >= 0 && isRegUsed[tempReg1]) isRegUsed[tempReg1] = 0;

               globalAux1 = endAux1;
               globalAux2 = NULL;
            }
            
         }
      }
      break; /* IdK */

   case FuncK:
      if (tree->declaracao)
      {
         char *auxType;
         if (tree->type == Integer)
            auxType = "int";
         else
            auxType = "void";
         endAux1 = criaEnd(String, auxType, -1);
         endAux2 = criaEnd(String, tree->attr.name, -1);

         insereQuad(fun, endAux1, endAux2, NULL);
         // argumentos da funcao, caso existam
         if (tree->qtdArgumentos > 0)
            cGen(tree->child[0], tree);
         cGen(tree->child[1], tree);
         insereQuad(end, endAux2, NULL, NULL);
      }
      break; /* FuncK*/

   default:
      break;
   }
} /* genExp */

/* Procedure genEsp generates code at an especificator node */
static void genEsp(TreeNode *tree)
{
   cGen(tree->child[0], tree);
   //printf("aaaaaaaaaaa");
   //printf("%s", tree->child[0]->attr.name);
} /* genEsp */

/* Procedure cGen recursively generates code by
 * tree traversal
 */
void cGen(TreeNode *tree, TreeNode *parent)
{
   // printQuads();
   if (tree != NULL)
   {
      switch (tree->nodekind)
      {
      case StmtK:
         genStmt(tree);
         break;
      case ExpK:
         genExp(tree, parent);
         break;
      case EspK:
         //printf("espppppppp\n");
         genEsp(tree);
         break;
      default:
         break;
      }
      if (tree->nodekind = EspK && tree->child[0] != NULL && tree->child[0]->declaracao && tree->child[0]->isArg){

      }
      else
      cGen(tree->sibling, parent);
   }
}

void printEnd(Endereco *endAux)
{
   if (endAux == NULL)
      printf("-");
   else
   {
      if (endAux->tipo == String)
         printf("%s", endAux->conteudo.nome);
      else
         printf("%d", endAux->conteudo.val);
   }
}

void printQuad(Quad *aux){
   printf("(");

      switch (aux->op)
      {
      case param:
         printf("PARAM,");
         break;
      case ret:
         printf("RET,");
         break;
      case call:
         printf("CALL,");
         break;
      case arg:
         printf("ARG,");
         break;
      case gotolab:
         printf("GOTO,");
         break;
      case iffalse:
         printf("IFF,");
         break;
      case lab:
         printf("LAB,");
         break;
      case load:
         printf("LOAD,");
         break;
      case store:
         printf("STORE,");
         break;
      case add:
         printf("ADD,");
         break;
      case sub:
         printf("SUB,");
         break;
      case divOp:
         printf("DIV,");
         break;
      case mult:
         printf("MULT,");
         break;
      case lt:
         printf("LT,");
         break;
      case lte:
         printf("LTE,");
         break;
      case gt:
         printf("GT,");
         break;
      case gte:
         printf("GTE,");
         break;
      case eq:
         printf("EQ,");
         break;
      case assign:
         printf("ASSIGN,");
         break;
      case fun:
         printf("FUN,");
         break;
      case aloc:
         printf("ALOC,");
         break;
      case end:
         printf("END,");
         break;
      case halt:
         printf("HALT,");
         break;
      default:
         printf("???,");
         break;
      }

      printEnd(aux->end1);
      printf(",");
      printEnd(aux->end2);
      printf(",");
      printEnd(aux->end3);

      printf(")\n");
}

void printQuads(){
   Quad *aux = raizLista;
   while (aux != NULL)
   {
      printQuad(aux);
      aux = aux->next;
   }
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
rStruct* codeGen(TreeNode *syntaxTree)
{
   /* generate code for Cmenos program */
   //printf("a\n");
   cGen(syntaxTree, NULL);
   /* finish */
   //printf("b\n");
   insereQuad(halt, NULL, NULL, NULL);
   //printf("c\n");
   printQuads();
   //printf("d\n");
   rStruct *retornoAux = (rStruct *) malloc(sizeof(rStruct));
   retornoAux->raiz = raizLista;
   retornoAux->regs = isRegUsed;
   return retornoAux;
}