/* ideia para controlar os registradores em uso:
 * liberar os registradores das atribuições, das menções de vetores,
 * das chamadas de função e parametros
 */

#include "globals.h"
#include "util.h"
#include "symtab.h"
#include "code.h"
#include "agen.h"
#include "string.h"
#include "stdlib.h"

#define STRING_TAM 10
#define INT_MEM_BYTES 32
#define REG_FRAME 30
//#define TOTAL_MEM 64

//int isMemUsed[TOTAL_MEM] = {0};

int currLineno = 0;
char *currEscopo = NULL;

instA *raizListaA = NULL;

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash ( char * key )
{ int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  { temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

/* the hash table */
static BucketList hashTable[SIZE];


/* prototype for internal recursive code generator */
void aGen(Quad *currQuad);

void insereAssembly(TipoA tipo, OperacaoA op, int rs, int rt, int rd, int im)
{
   instA *newNode = (instA *)malloc(sizeof(instA));
   newNode->tipoInst = tipo;
   newNode->opA = op;
   newNode->rs = rs;
   newNode->rt = rt;
   newNode->rd = rd;
   newNode->im = im;
   newNode->line = currLineno++;
   newNode->next = NULL;

   if (raizListaA == NULL)
      raizListaA = newNode;
   else
   {
      instA *auxNode = raizListaA;
      while (auxNode->next != NULL)
         auxNode = auxNode->next;

      auxNode->next = newNode;
   }
}

void insereHash(char *nome, char *escopo, int tam){
    char * busca = (char *) malloc(sizeof(char));
    strcpy(busca,escopo);
    //if (nome != NULL) strcat(busca,nome);
    int h = hash(busca);
    BucketList l =  hashTable[h];
    while ((l != NULL) && (strcmp(busca,l->name) != 0))
        l = l->next;
    
    if (l == NULL){ /* variable not yet in table */
        l = (BucketList) malloc(sizeof(struct BucketListRec));
        if (strcmp(busca,"global") != 0) l->lineno = currLineno;
        else l->lineno = -1;
        l->name = escopo;
        l->vars = NULL;
        if(nome != NULL){
            l->vars = (VarList) malloc(sizeof(struct VarListRec));
            l->vars->memloc = 0;
            l->vars->tam = tam;
            l->vars->name = nome;
            l->vars->next = NULL;
        }
        //l->calling = -1;
        l->next = hashTable[h];
        hashTable[h] = l; 
    }
    else{
        VarList t = l->vars;
        if (t == NULL){
            l->vars = (VarList) malloc(sizeof(struct VarListRec));
            l->vars->memloc = 0;
            l->vars->tam = tam;
            l->vars->name = nome;
            l->vars->next = NULL;
        }
        else{
            while (t->next != NULL) t = t->next;
            t->next = (VarList) malloc(sizeof(struct VarListRec));
            t->next->memloc = t->memloc + t->tam;
            t->next->name = nome;
            t->next->next = NULL;
        }
    }
}

int buscaRegLivreA(int isRegUsed[]){
   int i;
   for(i = 0; i < TOTAL_REGS; i++)
      if(!isRegUsed[i]) {
         isRegUsed[i] = 1;
         return i;
      }
}

VarList buscaHash(char *escopo, char *nome){
    int h = hash(escopo);
    BucketList l =  hashTable[h];
    while ((l != NULL) && (strcmp(escopo,l->name) != 0))
        l = l->next;
    VarList t = l->vars;
    while (strcmp(t->name, nome) != 0 && t->next != NULL) t = t->next;
    if (strcmp(t->name, nome) != 0) return buscaHash("global", nome);
    return t;
}

void aGen(Quad *currQuad){
    if (currQuad != NULL){
        switch (currQuad->op)
        {
        case store: /*PAREI AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII*/
        {
            if (currQuad->end3 == NULL){
                // registrador para guardar o imediato do store
                int regAux1 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux1] = 1;
                insereAssembly(tipoI, loadiA, -1, regAux1, -1, currQuad->end2->conteudo.val);
                // posicao da memoria da variavel
                int regAux2 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux2] = 1;
                VarList varListAux = buscaHash(currEscopo, currQuad->end1->conteudo.nome);
                insereAssembly(tipoI, addiA, REG_FRAME, regAux2, -1, varListAux->memloc);
                insereAssembly(tipoI, storeA, regAux2, regAux1, -1, 0);
            }
            break;
        }
        case aloc:
        {
            /* variavel comum (nao vetor) */
            if (currQuad->end3 == NULL){
                insereHash(currQuad->end1->conteudo.nome, currQuad->end2->conteudo.nome, 1);
            }
            else insereHash(currQuad->end1->conteudo.nome, currQuad->end3->conteudo.nome, currQuad->end2->conteudo.val);
            break;
        }
        /* inserindo a linha em que a função começa na tabela hash */
        case fun:
            {
                //printf("entrou no fun\n");
                char *escopo = currQuad->end2->conteudo.nome;
                currEscopo = escopo;
                if (!strcmp(escopo, "main")) {
                    insereAssembly(tipoI, loadiA, -1, REG_FRAME, -1, 0);
                    insereAssembly(tipoI, addiA, REG_FRAME, REG_FRAME, -1, 1);
                }
                else insereAssembly(tipoI, addiA, REG_FRAME, REG_FRAME, -1, 1);
                
                insereHash(NULL, escopo, 0);
                
                //printf("saiu do fun\n");
                break; /* end fun*/
            }
        case halt:
        {
            //printf("entrou no halt\n");
            insereAssembly(tipoJ, haltA, -1, -1, -1, -1);
            //printf("saiu do halt\n");
            break;
        }
        default:
            break;
        }
        aGen(currQuad->next);
    }
    return;
}

void printAssembly(){
   instA *aux = raizListaA;
   while (aux != NULL)
   {
      switch (aux->opA)
      {
      case storeA:
        printf("store");
        break;
      case loadiA:
        printf("loadi");
        break;
      case addiA:
         printf("addi");
         break;;
      case haltA:
         printf("halt\n");
         return;
         break;
      default:
         printf("???");
         break;
      }
      
      printf("%c", 9);
      
      if (aux->tipoInst == tipoR){
        if(aux->rd != -1) {
            printf("r%d", aux->rd);
            printf("%c", 9);
        }
        if(aux->rs != -1) {
            printf("r%d", aux->rs);
            printf("%c", 9);
        }
        if(aux->rt != -1) printf("r%d", aux->rt);
      }
      else if (aux->tipoInst == tipoI){
        if(aux->rt != -1) {
            printf("r%d", aux->rt);
            printf("%c", 9);
        }
        
        if(aux->rs != -1) {
            printf("r%d", aux->rs);
            printf("%c", 9);
        }
        if(aux->opA != notA && aux->opA != outA) printf("%d", aux->im);
      }
      else{
        printf("%d", aux->im);
      }

      printf("\n");
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
void assemblyGen(rStruct *interAux)
{
    //printf("a\n");
    Quad *quadAux = interAux->raiz;
    //printf("b\n");
    aGen(quadAux);
    //printf("c\n");
    printAssembly();
    printf("d\n");
}