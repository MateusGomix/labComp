#include "globals.h"
#include "symtab.h"
#include "analyze.h"
#include "util.h"

/* counter for variable memory locations */
static int location = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL && !Error)
  { preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t)
{
  char * tipo;
  switch(t->type){
    case Void: tipo = "void"; break;
    case Integer: tipo = "int"; break;
    case Boolean: tipo = "bool"; break;
    default: tipo = "\0"; break;
  }

  switch (t->nodekind)
  { 
    case ExpK:

      switch (t->kind.exp)
      { 
        
        case IdK:
        case FuncK:

          /* Esse par de nome e escopo não está na tabela */
          if (st_lookup(t->attr.name, t->escopo) == -1)  
          {

            // O nome da variável já foi declarado como função - ERRO 7
            if(!strcmp(t->tipoID,"var") && st_lookup(t->attr.name, "\0") != -1){

              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);

            }
            
            // É uma variável que foi declarada globalmente 
            else if (st_lookup(t->attr.name,"global") != -1 && t->declaracao == 0){

              st_insert(t->attr.name,t->lineno,0,tipo,"global",t->tipoID,0,0,t);

            }

            // O par atual nome e escopo é uma nova declaração 
            else if(t->declaracao == 1){

              // Declaração de função ou variável do tipo int 
              if(!strcmp(t->tipoID,"fun") || (!strcmp(t->tipoID,"var") && t->type == Integer)){

                // Declaração de função 
                if(!strcmp(t->tipoID,"fun")) {

                  // O main deve excepcionalmente ser do tipo void e 
                  // não possuir argumentos void main(void) 
                  if(!strcmp(t->attr.name,"main")){
                    if(t->type == Integer || t->qtdArgumentos > 0){
                      Error = 1;
                      fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);
                    }
                    else st_insert(t->attr.name,t->lineno,location++,tipo,t->escopo,t->tipoID,t->qtdArgumentos,0,t);
                  }
                  // E o output deve ter um argumento
                  else if(!strcmp(t->attr.name,"output")){
                    st_insert(t->attr.name,t->lineno,location++,tipo,t->escopo,t->tipoID,1,0,t);
                    t->qtdArgumentos = 1;
                  }
                  // Declaração de função qualquer
                  else st_insert(t->attr.name,t->lineno,location++,tipo,t->escopo,t->tipoID,t->qtdArgumentos,0,t);
                
                }
                // Declaração de variável int
                else st_insert(t->attr.name,t->lineno,location++,tipo,t->escopo,t->tipoID,0,t->vetor,t);
                
              }
              // Declaração de variável void - ERRO 3
              else{

                Error = 1;
              fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);

              }

            }
            // Utilização de uma variável não declarada - ERROS 1 E 5
            else{

              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);

            }
          }

          // O par nome e escopo já está inserido na tabela
          else{

            // Se o id for fun, então é uma ativação de função
            // e podemos recuperar o tipo de retorno e a quantidade
            // de argumentos para o nó da ativação
            if(!strcmp(t->tipoID,"fun")){

              char * salvaTipo =  retornaTipoFuncK(t->attr.name);
              t->qtdArgumentos = retornaArgsFuncK(t->attr.name);

              if(!strcmp(salvaTipo,"int")) t->type = Integer;
              else t->type = Void;

            }

            // Atualizando as linhas existentes da tabela 
            // se não for uma declaração ou se forem as 
            // funções input e output
            if(t->declaracao == 0 || !strcmp(t->attr.name,"input") || !strcmp(t->attr.name,"output")){

              // Se for um output aproveitamos para atualizar a sua
              // quantidade de argumentos 
              if(!strcmp(t->attr.name,"output")){

                st_insert(t->attr.name,t->lineno,0,tipo,t->escopo,t->tipoID,1,0,t);
                t->qtdArgumentos = 1;

              }

              else st_insert(t->attr.name,t->lineno,0,tipo,t->escopo,t->tipoID,0,0,t);

            }

            // ERRO 4
            else{

              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);

            }
          }

        break;

        default:
          break;

      }
    break;

    default:
      break;

  }

}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

// Variáveis auxiliares para a função erroSemantico
int retornou = 0; // quantidade de retornos
int tipoRetorno = 0; // tipo de retorno 0 = void, 1 = int
int linhaRetorno; // linha da função caso ela nunca retorne
char *escopoRetorno; // nome da função caso ela nunca retorne
/* Essa função varre a árvore depois de montar a 
 * tabela de símbolos, verificando alguns tipos de 
 * erros semânticos como função sem retorno ou retorno 
 * incorreto, argumentos de ativações, etc */
static void erroSemantico(TreeNode * t)
{ 
  switch (t->nodekind)
  { 
    
    case ExpK:
      
      switch (t->kind.exp)
      { 
        
        case FuncK:

          // A última função inteira não retornou
          if(tipoRetorno == 1 && retornou == 0){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",escopoRetorno,linhaRetorno);
          }

          if(t->type == Integer) {

            retornou = 0;
            tipoRetorno = 1;

          }
          else{

            retornou = 0;
            tipoRetorno = 0;

          }

          escopoRetorno = t->attr.name;
          linhaRetorno = t->lineno;

        break;
        
        case OpK:

          // Erro de operação com ponteiros
          if(t->child[0]->vetor == 1 && t->child[0]->child[0] == NULL){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
          
          }
          if(t->child[1]->vetor == 1 && t->child[1]->child[0] == NULL){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[1]->attr.name,t->child[1]->lineno);
          
          }

          // Erros de operação com voids
          if ((t->child[0]->type == Void)){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
          
          }
          if ((t->child[1]->type == Void)){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[1]->attr.name,t->child[1]->lineno);
          
          }
          
          break;

        case IdK:

          // Não vetor com filho
          if(!t->vetor && t->child[0] != NULL && !strcmp(t->tipoID,"var")){
            
            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);
          
          }

          // Se a constante do vetor for negativa é um erro
          else if(t->vetor && t->child[0] != NULL && t->child[0]->kind.exp == ConstK){
            
            if(t->child[0]->attr.val < 0){
              
              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
            
            }
          }

          // Vetor com índice ponteiro e função void
          else if(t->vetor && t->child[0] != NULL && t->child[0]){
            
            // Filho é vetor e é ponteiro
            if(t->child[0]->vetor && t->child[0]->child[0] == NULL){
              
              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
            
            }

            // Filho é função e é void
            if(t->child[0]->type == Void){
              
              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
            
            }

          }

          // Verificando os argumentos de uma função: 
          // quantidade, tipo(int) e ponteiros 
          if(!strcmp(t->tipoID,"fun")){
            //printf("entrou na condicao de verificar argumentos de funcao\n");

            int auxArgs = 0;
            for(TreeNode *aux = t->child[0]; aux != NULL; aux = aux->sibling){

              auxArgs++;
              if(aux->type == Void){

                Error = 1;
                fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",aux->attr.name,aux->lineno);

              }
            }

            //printf("saiu do primeiro for\n");

            if(auxArgs != t->qtdArgumentos){

              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);

            }

            //printf("saiu do if de qtd\n");

            // Verificando se os parâmetros vetores e não vetores batem batem 
            if(t->qtdArgumentos > 0){

              if(!strcmp(t->attr.name,"output")){

                if(t->child[0]->vetor == 1 && t->child[0]->child[0] == NULL){

                  Error = 1;
                  fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
                
                }
              }

              else{
                /* ERRO NO CODIGO INTERMEDIARIO PODE ESTAR POR AQUI */
                TreeNode *declAux = retornaNo(t->attr.name,t->escopo);
                declAux = declAux->child[0];
                TreeNode *ativAux = t->child[0];

                //printf("saiu dos retornos de definicao da func\n");

                while(declAux != NULL && ativAux != NULL){
                  //printf("entrou no while de tipo\n");

                  if(declAux->child[0]->vetor != ativAux->vetor){
                    //printf("entrou no if de vetores incompativel\n");

                    if(ativAux->vetor == 1 && ativAux->child[0] == NULL){

                      Error = 1;
                      fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",ativAux->attr.name,ativAux->lineno);
                      break;
                    
                    }
                    else if(ativAux->vetor == 0){
                      //printf("ENTROU AQUI OOOOOOOOOOOOOOOOOOOOOOO");

                      Error = 1;
                      if(ativAux->kind.exp == ConstK) fprintf(listing,"ERRO SEMANTICO: %d LINHA: %d\n",ativAux->attr.val,ativAux->lineno);
                      else fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",ativAux->attr.name,ativAux->lineno);
                      break;

                    }
                  }
                  else if(declAux->child[0]->vetor && ativAux->vetor && ativAux->child[0] != 0){
                      Error = 1;
                      fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",ativAux->attr.name,ativAux->lineno);
                      break;
                  }
                  //printf("indo para os irmaos\n");
                  declAux = declAux->sibling;
                  ativAux = ativAux->sibling;
                  //printf("fim do while de tipo\n");
                }
              }
            }
            //printf("saiu da condicao de verificar argumentos de funcao\n");
          }

          break;

        default:
          break;

      }

      break;

    case StmtK:

      switch (t->kind.stmt)
      { 

        case RetornoK:

          // Retorno de ponteiro
          if(t->child[0] != NULL &&t->child[0]->vetor && t->child[0]->child[0] == NULL){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);

          }
        
          // Estamos aguardando um retorno inteiro
          if(tipoRetorno == 1){

            // Se esse nó de retorno for vazio ou tiver uma função vazia é um erro
            if(t->child[0] == NULL || t->child[0]->type == Void){

              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: return LINHA: %d\n",t->lineno);

            }
            else retornou++;
          }

          // Não estamos aguardando um retorno, 
          // logo a função em que estamos é void, 
          // então este retorno deve ser vazio
          else{

            if(t->child[0] != NULL && t->child[0]->type != Void){

              Error = 1;
              fprintf(listing,"ERRO SEMANTICO: return LINHA: %d\n",t->lineno);
            
            }
          }

        break;

        case IfK:

          /* Verifica se o argumento do if é void */
          if (t->child[0]->type == Void){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
          
          }

          /* Verifica se o argumento do if é ponteiro */
          if(t->child[0] != NULL && t->child[0]->vetor && t->child[0]->child[0] == NULL){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
          
          }

          break;

        case RecebeK:

          /* Verifica se o lado direito da atribuição é void - ERRO 2 */
          if (t->child[1]->type != Integer){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[1]->attr.name,t->child[1]->lineno);
          
          }

          // Verifica se um dos lados da atribuição é ponteiro
          if(t->child[0]->vetor && t->child[0]->child[0] == NULL){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
          
          }

          if(t->child[1]->vetor && t->child[1]->child[0] == NULL){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[1]->attr.name,t->child[1]->lineno);
          
          }

          break;
        
        case WhileK:

          /* Verifica se o argumento do while é void */
          if (t->child[0]->type == Void){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
          
          }

          /* Verifica se o argumento do while é ponteiro */
          if(t->child[0] != NULL && t->child[0]->vetor && t->child[0]->child[0] == NULL){

            Error = 1;
            fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->child[0]->attr.name,t->child[0]->lineno);
          
          }

          break;

        default:
          break;

      }

      break;

    default:
      break;

  }
}

void verificaTipo(TreeNode * syntaxTree)
{ 
  traverse(syntaxTree,erroSemantico,nullProc);
  //printf("saiu do traverse do verificaTipo\n");
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ traverse(syntaxTree,insertNode,nullProc);
  //printf("saiu do traverse\n");
  
  verificaTipo(syntaxTree);
  //printf("saiu do verificaTipo\n");

  if (TraceAnalyze && !Error)
  { fprintf(listing,"\nTabela de Simbolos:\n");
    printSymTab(listing);
  }
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ 
  
  switch (t->nodekind)
  { 
    
    case ExpK:
      
      switch (t->kind.exp)
      { 
        
        case OpK:
          
          if ((t->attr.op == IGUAL) || (t->attr.op == MENOR) || (t->attr.op == MAIOR) || (t->attr.op == MAIORIG) || (t->attr.op == MENORIG))
            
            t->type = Boolean;

          else

            t->type = Integer;

        break;

        case ConstK: t->type = Integer; break;

        case IdK:

          if(strcmp(t->attr.name, "input") == 0 || strcmp(t->tipoID,"var") == 0 )t->type = Integer;

          break;

        default:
          break;

      }

      break;

    case StmtK:

      switch (t->kind.stmt)
      { 
        
        case IfK:
        break;

        case RecebeK:

          t->type = Integer;

        break;
        
        case WhileK:
          break;

        default:
          break;

      }

      break;

    case EspK:

      if(t->kind.esp == VoidK) t->child[0]->type = Void;
      else t->child[0]->type = Integer;

    break;

    default:
      break;

  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}

char * escopo = "global";
int qtdMain = 0;
/* Função que principalmente salva o escopo das variáveis, 
 * também verifica a existência de uma única main
 */
void salvaEscopo( TreeNode * t)
{ 
  if (t != NULL && !Error){ 

    if(strcmp(t->tipoID, "fun") == 0) {

      if(t->kind.exp == FuncK) {

        /* Contagem de argumentos de função */
        for(TreeNode *aux = t->child[0]; aux != NULL; aux = aux->sibling){

          t->qtdArgumentos = t->qtdArgumentos + 1;

        }

        escopo = copyString(t->attr.name);

        // Contagem de mains
        if(!strcmp(t->attr.name,"main")) qtdMain++;

        // Qualquer função declarada depois da main é um erro
        else if(qtdMain > 0){

          Error = 1;
          fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);

        }

        // Se em algum momento houverem 2 mains é um erro
        if(qtdMain > 1){

          Error = 1;
          fprintf(listing,"ERRO SEMANTICO: %s LINHA: %d\n",t->attr.name,t->lineno);

        }
      }

      // Decidimos que o escopo das funções seria vazio 
      t->escopo = "\0";

    }
    else if(strcmp(t->tipoID, "var") == 0) t->escopo = escopo;
    
    int i;
    for (i=0; i < MAXCHILDREN; i++)
      salvaEscopo(t->child[i]);
    
    if(t->kind.exp == FuncK)escopo = "global";
    salvaEscopo(t->sibling);
  }
}