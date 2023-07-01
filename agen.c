/* ideia para controlar os registradores em uso:
 * liberar os registradores das atribuições, das menções de vetores,
 * das chamadas de função e parametros
 */

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "agen.h"
#include "string.h"
#include "stdlib.h"

#define TOTAL_LABELS 50
#define STRING_TAM 10
#define REG_PILHA 29
#define REG_FRAME 30
#define REG_RA 31
#define FRAME_SIZE 32
//#define TOTAL_MEM 64

//int isMemUsed[TOTAL_MEM] = {0};

int currLineno = 0;
/*talvez esse currEscopo de problema*/
char *currEscopo = "global";

int labelsVet[TOTAL_LABELS];

instA *raizListaA = NULL;

TPilhaReg *pilhaDeRegs = NULL;

TPilhaReg* criaPilhaReg(){
  TPilhaReg *pilha = (TPilhaReg*) malloc(sizeof(TPilhaReg));
  pilha->tam = 0;
  pilha->topo = NULL;
  return pilha;
}

TItemReg* criaItemReg(int *elem){
  TItemReg *item = (TItemReg*) malloc(sizeof(TItemReg));
  item->regsEmpilhados = elem;
  item->prox = NULL;
  return item;
}

void addPilhaReg(TPilhaReg *pilha, int *elem){
  TItemReg *aux = criaItemReg(elem);
  
  if(pilha->tam == 0){
    pilha->topo = aux;
  }
  else{
    aux->prox = pilha->topo;
    pilha->topo = aux;
  }
  pilha->tam += 1;
}

int* popPilhaReg(TPilhaReg *pilha){
  TItemReg *aux = pilha->topo;
  pilha->topo = aux->prox;
  pilha->tam -= 1;
  return aux->regsEmpilhados;
}

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
void printAssembly(instA *aux);

instA* insereAssembly(TipoA tipo, OperacaoA op, int rs, int rt, int rd, int im)
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
   return newNode;
}

void insereHash(char *nome, char *escopo, int tam, int isVetArg){
    char * busca = (char *) malloc(sizeof(char));
    strcpy(busca,escopo);
    //if (nome != NULL) strcat(busca,nome);
    int h = hash(busca);
    BucketList l =  hashTable[h];
    while ((l != NULL) && (strcmp(busca,l->name) != 0))
        l = l->next;
    
    if (l == NULL){ /* escopo not yet in table */
        l = (BucketList) malloc(sizeof(struct BucketListRec));
        // onde começa cada escopo/funcao, global não tem um inicio pois nao é funcao
        if (strcmp(busca,"global") != 0) l->lineno = currLineno;
        else l->lineno = -1;
        l->name = escopo;
        l->vars = NULL;
        if(nome != NULL){
            l->vars = (VarList) malloc(sizeof(struct VarListRec));
            l->vars->memloc = 0;
            l->vars->tam = tam;
            l->vars->name = nome;
            l->vars->isVetArg = isVetArg;
            l->vars->next = NULL;
        }
        //l->calling = -1;
        l->next = hashTable[h];
        hashTable[h] = l; 
    }
    // escopo existe, add mais uma variável àquele escopo
    else{
        VarList t = l->vars;
        if (t == NULL){
            l->vars = (VarList) malloc(sizeof(struct VarListRec));
            l->vars->memloc = 0;
            l->vars->tam = tam;
            l->vars->name = nome;
            l->vars->isVetArg = isVetArg;
            l->vars->next = NULL;
        }
        else{
            while (t->next != NULL) t = t->next;
            t->next = (VarList) malloc(sizeof(struct VarListRec));
            t->next->memloc = t->memloc + t->tam;
            t->next->name = nome;
            t->next->isVetArg = isVetArg;
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

BucketList buscaHashEscopo(char *escopo){
    int h = hash(escopo);
    BucketList l =  hashTable[h];
    while ((l != NULL) && (strcmp(escopo,l->name) != 0))
        l = l->next;
    return l;
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

instA *auxPrintA;
//int paramCont = 0;
int regAuxOutput = -1;

instA *empilha(Quad *currQuad, int regAux2){
  int regAux1 = buscaRegLivreA(currQuad->regsUsados);
  currQuad->regsUsados[regAux1] = 1;
  // início do frame posterior, ou final do frame atual em regAux1
  instA *PrintARet = insereAssembly(tipoI, addiA, REG_FRAME, regAux1, -1, 1);
  insereAssembly(tipoI, multiA, regAux1, regAux1, -1, FRAME_SIZE);
  insereAssembly(tipoI, subiA, regAux1, regAux1, -1, 1);
  
  // localizando onde parou a pilha
  insereAssembly(tipoI, addiA, REG_PILHA, REG_PILHA, -1, 1);
  insereAssembly(tipoR, subA, regAux1, REG_PILHA, regAux1, -1);

  // guardando na memoria
  insereAssembly(tipoI, storeA, regAux1, regAux2, -1, 0);

  currQuad->regsUsados[regAux1] = 0;

  return PrintARet;
}

void empilhaRegPilhaEspecial(Quad *currQuad, int regAux2){
  int regAux1 = buscaRegLivreA(currQuad->regsUsados);
  currQuad->regsUsados[regAux1] = 1;
  // início do frame posterior, ou final do frame atual em regAux1
  insereAssembly(tipoI, addiA, REG_FRAME, regAux1, -1, 1);
  insereAssembly(tipoI, multiA, regAux1, regAux1, -1, FRAME_SIZE);
  insereAssembly(tipoI, subiA, regAux1, regAux1, -1, 1);

  // guardando na memoria
  insereAssembly(tipoI, storeA, regAux1, regAux2, -1, 0);
  currQuad->regsUsados[regAux1] = 0;
}

void desempilha(Quad *currQuad, int regAux2){
  int regAux1 = buscaRegLivreA(currQuad->regsUsados);
  currQuad->regsUsados[regAux1] = 1;
  
  // início do frame posterior, ou final do frame atual em regAux1
  insereAssembly(tipoI, addiA, REG_FRAME, regAux1, -1, 1);
  insereAssembly(tipoI, multiA, regAux1, regAux1, -1, FRAME_SIZE);
  insereAssembly(tipoI, subiA, regAux1, regAux1, -1, 1);
  insereAssembly(tipoR, subA, regAux1, REG_PILHA, regAux1, -1);

  // decremento da pilha
  insereAssembly(tipoI, subiA, REG_PILHA, REG_PILHA, -1, 1);

  insereAssembly(tipoI, loadA, regAux1, regAux2, -1, 0);

  currQuad->regsUsados[regAux1] = 0;
}

void desempilhaRegPilhaEspecial (Quad *currQuad, int regAux2){
  int regAux1 = buscaRegLivreA(currQuad->regsUsados);
  currQuad->regsUsados[regAux1] = 1;
  
  // início do frame posterior, ou final do frame atual em regAux1
  insereAssembly(tipoI, addiA, REG_FRAME, regAux1, -1, 1);
  insereAssembly(tipoI, multiA, regAux1, regAux1, -1, FRAME_SIZE);
  insereAssembly(tipoI, subiA, regAux1, regAux1, -1, 1);

  insereAssembly(tipoI, loadA, regAux1, regAux2, -1, 0);

  currQuad->regsUsados[regAux1] = 0;
}

void aGen(Quad *currQuad){
  auxPrintA = NULL;
    if (currQuad != NULL){
        printQuad(currQuad);
        switch (currQuad->op)
        {
        case lab:
        {
          labelsVet[currQuad->end1->label] = currLineno;
          break;
        }
        case ret:
        {
          //for(int i = 0; i < TOTAL_REGS; i++) printf("%d", currQuad->regsUsados[i]);
          int regAux1 = buscaRegLivreA(currQuad->regsUsados);
          currQuad->regsUsados[regAux1] = 1;
          auxPrintA = insereAssembly(tipoI, moveA, REG_RA, regAux1, -1, 0);
          insereAssembly(tipoI, addiA, regAux1, regAux1, -1, 1);
          
          insereAssembly(tipoI, subiA, REG_FRAME, REG_FRAME, -1, 1);
          
          desempilhaRegPilhaEspecial(currQuad, REG_PILHA);

          desempilha(currQuad, REG_RA);
          desempilha(currQuad, REG_FRAME);
          int regRet = 0;
          if (currQuad->end1 != NULL) regRet = currQuad->end1->regPos;
          empilha(currQuad, regRet);

          insereAssembly(tipoR, jrA, -1, regAux1, -1, -1);

          break;
        }
        case arg: /* PAREI AQUI AAAAAAAAAAAAAAAAAAAAAAAA */
        {
          //printf("entrou aquiiii");
          // criando a variável na hash
          // verificar aqui se é vetor <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
          int isVetAux = 0;
          if (currQuad->end3 != NULL) isVetAux = 1;
          insereHash(currQuad->end1->conteudo.nome, currQuad->end2->conteudo.nome, 1, isVetAux);

          int regAux1 = buscaRegLivreA(currQuad->regsUsados);
          currQuad->regsUsados[regAux1] = 1;
          // início do frame posterior, ou final do frame atual em regAux1
          auxPrintA = insereAssembly(tipoI, addiA, REG_FRAME, regAux1, -1, 1);
          insereAssembly(tipoI, multiA, regAux1, regAux1, -1, FRAME_SIZE);
          insereAssembly(tipoI, subiA, regAux1, regAux1, -1, 1);
          insereAssembly(tipoR, subA, regAux1, REG_PILHA, regAux1, -1);

          // decremento da pilha
          insereAssembly(tipoI, subiA, REG_PILHA, REG_PILHA, -1, 1);

          int regAux2 = buscaRegLivreA(currQuad->regsUsados);
          currQuad->regsUsados[regAux2] = 1;
          insereAssembly(tipoI, loadA, regAux1, regAux2, -1, 0);

          VarList varListAux = buscaHash(currEscopo, currQuad->end1->conteudo.nome);
          insereAssembly(tipoI, multiA, REG_FRAME, regAux1, -1, FRAME_SIZE);
          insereAssembly(tipoI, addiA, regAux1, regAux1, -1, varListAux->memloc);
          insereAssembly(tipoI, storeA, regAux1, regAux2, -1, 0);

          break;
        }
        case param:
        {
            int regAux2 = currQuad->end1->regPos;
            instA *auxPrintA2;
            if(regAux2 < 0){
                regAux2 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux2] = 1;
                auxPrintA2 = insereAssembly(tipoI, loadiA, -1, regAux2, -1, currQuad->end1->conteudo.val);
            }
            if(strcmp(currQuad->next->end2->conteudo.nome, "output") == 0){
                regAuxOutput = regAux2;
            }
            else{
              int regAux1 = buscaRegLivreA(currQuad->regsUsados);
              currQuad->regsUsados[regAux1] = 1;
              // início do frame 2x posterior, ou final do próximo frame em regAux1
              auxPrintA = insereAssembly(tipoI, addiA, REG_FRAME, regAux1, -1, 2);
              insereAssembly(tipoI, multiA, regAux1, regAux1, -1, FRAME_SIZE);
              insereAssembly(tipoI, subiA, regAux1, regAux1, -1, 1);
              
              // localizando onde parou a pilha
              insereAssembly(tipoI, addiA, REG_PILHA, REG_PILHA, -1, 1);
              insereAssembly(tipoR, subA, regAux1, REG_PILHA, regAux1, -1);

              // guardando na memoria
              insereAssembly(tipoI, storeA, regAux1, regAux2, -1, 0);

              if(currQuad->end1->regPos < 0) auxPrintA = auxPrintA2;
            }
            break;
        }
        case call:
        {
            // call de input: do jeito que está agora, o input só funciona se for chamado ao igualar com uma variável
            if(strcmp(currQuad->end2->conteudo.nome, "input") == 0){
                if (currQuad->next->op == store){
                    //printf("ENTROU AQUI AAAAAAAA\n");
                    int imAux = 0;
                    int regAux1;
                    instA *auxPrintA2;

                    // posicao da memoria da variavel
                    regAux1 = buscaRegLivreA(currQuad->next->regsUsados);
                    currQuad->next->regsUsados[regAux1] = 1;
                    VarList varListAux = buscaHash(currEscopo, currQuad->next->end1->conteudo.nome);
                    auxPrintA = insereAssembly(tipoI, multiA, REG_FRAME, regAux1, -1, FRAME_SIZE);
                    insereAssembly(tipoI, addiA, regAux1, regAux1, -1, varListAux->memloc);
                    //printf("PAROU AQUI AAAAAAAA\n");
                    if (currQuad->next->end3 != NULL){
                        if(currQuad->next->end3->regPos < 0) insereAssembly(tipoI, addiA, regAux1, regAux1, -1, currQuad->next->end3->conteudo.val);
                        else insereAssembly(tipoR, addA, regAux1, currQuad->next->end3->regPos, regAux1, -1);
                    }
                    //printf("PAROU AQUI AAAAAAAA\n");
                    insereAssembly(tipoI, inA, regAux1, -1, -1, imAux);
                    //printf("PAROU AQUI AAAAAAAA\n");
                    // pulando o próximo store
                    currQuad = currQuad->next;
                    //printf("PAROU AQUI AAAAAAAA\n");
                }
            }
            // call de output
            else if(strcmp(currQuad->end2->conteudo.nome, "output") == 0){
              auxPrintA = insereAssembly(tipoI, outA, -1, regAuxOutput, -1, 0);
            }
            // outros
            else{
              //for(int i = 0; i < TOTAL_REGS; i++) printf("%d ", currQuad->regsUsados[i]);
              //printf("\n");
              for (int regAux2 = 0; regAux2 < TOTAL_REGS; regAux2++){
                //printf("antes: ");for(int i = 0; i < TOTAL_REGS; i++) printf("%d ", currQuad->regsUsados[i]);
                //printf("\n");
                if(currQuad->regsUsados[regAux2] == 1){
                  if(auxPrintA == NULL) auxPrintA = empilha(currQuad, regAux2);
                  else empilha(currQuad, regAux2);
                }
                //printf("depois: ");for(int i = 0; i < TOTAL_REGS; i++) printf("%d ", currQuad->regsUsados[i]);
                //printf("\n");
              }
              empilhaRegPilhaEspecial(currQuad, REG_PILHA);
              empilha(currQuad, REG_FRAME);
              empilha(currQuad, REG_RA);
              insereAssembly(tipoI, loadiA, -1, REG_PILHA, -1, currQuad->end3->conteudo.val);
              BucketList auxHash = buscaHashEscopo(currQuad->end2->conteudo.nome);
              insereAssembly(tipoJ, jalA, -1, -1, -1, auxHash->lineno);

              desempilha(currQuad, currQuad->end1->regPos); // retorno do call

              for (int regAux2 = TOTAL_REGS - 1; regAux2 >= 0; regAux2--){
                if(currQuad->regsUsados[regAux2] == 1){
                  desempilha(currQuad, regAux2);
                }
              }

            }
            break;
        }

        case gotolab:
        {
            auxPrintA = insereAssembly(tipoJ, jA, -1, -1, -1, currQuad->end1->label);
            break;
        }
        case eq:
        //case neq:
        {
            OperacaoA auxOp = bneA;
            instA *auxPrintA2, *auxPrintA3, *auxPrintA4;
            //if (currQuad->op == neq) auxOp = beqA;
            int regAux1 = currQuad->end2->regPos;
            int regAux2 = currQuad->end3->regPos;
            if(regAux1 < 0){
                regAux1 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux1] = 1;
                auxPrintA2 = insereAssembly(tipoI, loadiA, -1, regAux1, -1, currQuad->end2->conteudo.val);
            }
            if(regAux2 < 0){
                regAux2 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux2] = 1;
                auxPrintA3 = insereAssembly(tipoI, loadiA, -1, regAux2, -1, currQuad->end3->conteudo.val);
            }

            //lembrar de trocar o valor das labels pelo valor da linha
            auxPrintA = insereAssembly(tipoI, auxOp, regAux2, regAux1, -1, currQuad->next->end2->label);

            if (currQuad->end3->regPos < 0) auxPrintA = auxPrintA3;
            if (currQuad->end2->regPos < 0) auxPrintA = auxPrintA2;
            
            break;
        }
        case lt:
        case lte:
        case gt:
        case gte:
        {
            instA *auxPrintA2, *auxPrintA3, *auxPrintA4;
            int regAux1 = currQuad->end2->regPos;
            int regAux2 = currQuad->end3->regPos;
            if(regAux1 < 0){
                regAux1 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux1] = 1;
                auxPrintA2 = insereAssembly(tipoI, loadiA, -1, regAux1, -1, currQuad->end2->conteudo.val);
            }
            if(regAux2 < 0){
                regAux2 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux2] = 1;
                auxPrintA3 = insereAssembly(tipoI, loadiA, -1, regAux2, -1, currQuad->end3->conteudo.val);
            }

            if (currQuad->op == lt){
                auxPrintA = insereAssembly(tipoR, sltA, regAux1, regAux2, currQuad->end1->regPos, -1);
            }
            if (currQuad->op == lte){
                auxPrintA = insereAssembly(tipoI, addiA, regAux2, regAux2, -1, 1);
                insereAssembly(tipoR, sltA, regAux1, regAux2, currQuad->end1->regPos, -1);
            }
            if (currQuad->op == gt){
                int anotherRegAux = regAux1;
                regAux1 = regAux2;
                regAux2 = regAux1;
                auxPrintA = insereAssembly(tipoR, sltA, regAux1, regAux2, currQuad->end1->regPos, -1);
            }
            if (currQuad->op == gte){
                int anotherRegAux = regAux1;
                regAux1 = regAux2;
                regAux2 = regAux1;
                auxPrintA = insereAssembly(tipoI, addiA, regAux2, regAux2, -1, 1);
                insereAssembly(tipoR, sltA, regAux1, regAux2, currQuad->end1->regPos, -1);
            }

            if (currQuad->end3->regPos < 0) auxPrintA = auxPrintA3;
            if (currQuad->end2->regPos < 0) auxPrintA = auxPrintA2;

            int regAux3 = buscaRegLivreA(currQuad->regsUsados);
            currQuad->regsUsados[regAux3] = 1;
            insereAssembly(tipoI, loadiA, -1, regAux3, -1, 1);

            insereAssembly(tipoI, beqA, currQuad->end1->regPos, regAux3, -1, currQuad->next->end2->label);

            break;
        }
        case load:
        {
            int imAux = 0;
            if(currQuad->end3 != NULL && currQuad->end3->regPos < 0) imAux = currQuad->end3->conteudo.val;
            //printf("saiu daqui\n");
            VarList varListAux = buscaHash(currEscopo, currQuad->end2->conteudo.nome);
            int regAux1 = buscaRegLivreA(currQuad->regsUsados);
            auxPrintA = insereAssembly(tipoI, multiA, REG_FRAME, regAux1, -1, FRAME_SIZE);
            insereAssembly(tipoI, addiA, regAux1, regAux1, -1, varListAux->memloc);
            //printf("saiu daqui\n");
            if (currQuad->end3 != NULL && currQuad->end3->regPos >= 0) insereAssembly(tipoR, addA, regAux1, currQuad->end3->regPos, regAux1, varListAux->memloc);
            //printf("saiu daqui\n");
            insereAssembly(tipoI, loadA, regAux1, currQuad->end1->regPos, -1, imAux);
            //printf("saiu daqui\n");
            break;
        }
        case mult:
        case divOp:
        case add:
        case sub:
        {
            OperacaoA opAux;
            if (currQuad->op == add) opAux = addiA;
            else if (currQuad->op == sub) opAux = subiA;
            else if (currQuad->op == mult) opAux = multiA;
            else if (currQuad->op == divOp) opAux = diviA;
            // ambos são imediatos
            if(currQuad->end2->regPos < 0 && currQuad->end3->regPos < 0){
                int regAux1 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux1] = 1;
                auxPrintA = insereAssembly(tipoI, loadiA, -1, regAux1, -1, currQuad->end2->conteudo.val);
                insereAssembly(tipoI, opAux, regAux1, currQuad->end1->regPos, -1, currQuad->end3->conteudo.val);
            }
            // pelo menos um é imediato
            else if(currQuad->end2->regPos < 0 || currQuad->end3->regPos < 0){
                int regAux1 = currQuad->end2->regPos;
                if(regAux1 < 0){
                    regAux1 = buscaRegLivreA(currQuad->regsUsados);
                    currQuad->regsUsados[regAux1] = 1;
                    auxPrintA = insereAssembly(tipoI, loadiA, -1, regAux1, -1, currQuad->end2->conteudo.val);
                }
                instA *auxPrintA2 = insereAssembly(tipoI, opAux, regAux1, currQuad->end1->regPos, -1, currQuad->end3->conteudo.val);

                if(regAux1 >= 0) auxPrintA = auxPrintA2;
            }
            // ambos são regs
            else {
                if(currQuad->op == add) opAux = addA;
                else if (currQuad->op == sub) opAux = subA;
                else if (currQuad->op == mult) opAux = multA;
                else if (currQuad->op == divOp) opAux = divA;
                auxPrintA = insereAssembly(tipoR, opAux, currQuad->end2->regPos, currQuad->end3->regPos, currQuad->end1->regPos, -1);
            }

            break;
        }
        case store: /*PAREI AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII*/
        {
            if (currQuad->end3 == NULL){
                // registrador para guardar o imediato do store ou o reg com o devido valor
                int regAux1 = currQuad->end2->regPos;
                if(currQuad->end2->regPos < 0){
                    regAux1 = buscaRegLivreA(currQuad->regsUsados);
                    currQuad->regsUsados[regAux1] = 1;
                    auxPrintA = insereAssembly(tipoI, loadiA, -1, regAux1, -1, currQuad->end2->conteudo.val);
                }
                // posicao da memoria da variavel
                int regAux2 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux2] = 1;
                VarList varListAux = buscaHash(currEscopo, currQuad->end1->conteudo.nome);
                instA *auxPrintA2 = insereAssembly(tipoI, multiA, REG_FRAME, regAux2, -1, FRAME_SIZE);
                insereAssembly(tipoI, addiA, regAux2, regAux2, -1, varListAux->memloc);
                //insereAssembly(tipoI, multiA, REG_FRAME, regAux2, -1, FRAME_SIZE);
                insereAssembly(tipoI, storeA, regAux2, regAux1, -1, 0);

                if(currQuad->end2->regPos >= 0) auxPrintA = auxPrintA2;
            }
            else{
                //printf("entrou no else do store\n");
                //printf("%d %d\n", currQuad->end2->regPos, currQuad->end3->regPos);
                // registrador para guardar o imediato do store ou o reg com o devido valor
                int regAux1 = currQuad->end3->regPos;
                if(currQuad->end3->regPos < 0){
                    regAux1 = buscaRegLivreA(currQuad->regsUsados);
                    currQuad->regsUsados[regAux1] = 1;
                    auxPrintA = insereAssembly(tipoI, loadiA, -1, regAux1, -1, currQuad->end3->conteudo.val);
                }
                // posicao da memoria da variavel
                int regAux2 = buscaRegLivreA(currQuad->regsUsados);
                currQuad->regsUsados[regAux2] = 1;
                VarList varListAux = buscaHash(currEscopo, currQuad->end1->conteudo.nome);
                instA *auxPrintA2 = insereAssembly(tipoI, multiA, REG_FRAME, regAux2, -1, FRAME_SIZE);
                insereAssembly(tipoI, addiA, regAux2, regAux2, -1, varListAux->memloc);
                if (currQuad->end2->regPos < 0) insereAssembly(tipoI, addiA, regAux2, regAux2, -1, currQuad->end2->conteudo.val);
                else insereAssembly(tipoR, addA, regAux2, currQuad->end2->regPos, regAux2, -1);
                //insereAssembly(tipoI, multiA, REG_FRAME, regAux2, -1, FRAME_SIZE);
                insereAssembly(tipoI, storeA, regAux2, regAux1, -1, 0);

                if(currQuad->end3->regPos >= 0) auxPrintA = auxPrintA2;
            }
            break;
        }
        case aloc:
        {
            /* variavel comum (nao vetor) */
            if (currQuad->end3 == NULL){
                insereHash(currQuad->end1->conteudo.nome, currQuad->end2->conteudo.nome, 1, 0);
            }
            else insereHash(currQuad->end1->conteudo.nome, currQuad->end3->conteudo.nome, currQuad->end2->conteudo.val, 0);
            auxPrintA = NULL;
            break;
        }
        /* inserindo a linha em que a função começa na tabela hash */
        case fun:
            {
                //printf("entrou no fun\n");
                char *escopo = currQuad->end2->conteudo.nome;
                //PRINTANDO OS ESCOPOS AQUI 
                //printf(currEscopo);
                currEscopo = escopo;
                //printf(currEscopo);
                insereHash(NULL, escopo, 0, 0);
                if (!strcmp(escopo, "main")) {
                    auxPrintA = insereAssembly(tipoI, loadiA, -1, REG_FRAME, -1, 0);
                    insereAssembly(tipoI, addiA, REG_FRAME, REG_FRAME, -1, 1);
                    insereAssembly(tipoI, loadiA, -1, REG_PILHA, -1, 0);
                    insereAssembly(tipoI, loadiA, -1, REG_RA, -1, 0);
                }
                else auxPrintA = insereAssembly(tipoI, addiA, REG_FRAME, REG_FRAME, -1, 1);
                
                //printf("saiu do fun\n");
                break; /* end fun*/
            }
        case halt:
        {
            //printf("entrou no halt\n");
            auxPrintA = insereAssembly(tipoJ, haltA, -1, -1, -1, -1);
            //printf("saiu do halt\n");
            break;
        }
        default:
            auxPrintA = NULL;
            break;
        }
        if(auxPrintA == NULL) printf("----------\n");
        else printAssembly(auxPrintA);
        aGen(currQuad->next);
    }
    return;
}

void printAssembly(instA *aux){
   while (aux != NULL)
   {
      switch (aux->opA)
      {
      case outA:
        printf("out");
        break;
      case jrA:
        printf("jr");
        break;
      case moveA:
        printf("move");
        break;
      case jalA:
        printf("jal");
        break;
      case inA:
        printf("in");
        break;
      case sltA:
        printf("slt");
        break;
      case jA:
        printf("j");
        break;
      case beqA:
        printf("beq");
        break;
      case bneA:
        printf("bne");
        break;
      case divA:
        printf("div");
        break;
      case diviA:
        printf("divi");
        break;
      case multA:
        printf("mult");
        break;
      case multiA:
        printf("multi");
        break;
      case storeA:
        printf("store");
        break;
      case loadA:
        printf("load");
        break;
      case loadiA:
        printf("loadi");
        break;
      case subA:
        printf("sub");
        break;
      case subiA:
         printf("subi");
         break;
      case addA:
        printf("add");
        break;
      case addiA:
         printf("addi");
         break;
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

void ajustaJumps(instA *raiz){
  if(raiz != NULL){
    if (raiz->opA == jA) raiz->im = labelsVet[raiz->im];
  ajustaJumps(raiz->next);
  }
  return;
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
instA* assemblyGen(rStruct *interAux)
{
    //pilhaDeRegs = criaPilhaReg();
    //printf("a\n");
    Quad *quadAux = interAux->raiz;

    insereAssembly(tipoJ,jA, -1, -1, -1, 0);
    //printf("b\n");
    printf("\tTUPLAS E RESPECTIVO CODIGO:\n");
    aGen(quadAux);
    //printf("c\n");
    printf("--------------------------------------------------------------\n");
    ajustaJumps(raizListaA->next);
    BucketList hashAux = buscaHashEscopo("main");
    raizListaA->im = hashAux->lineno;
    printf("\tCODIGO ASSEMBLY COMPLETO E REFATORADO:\n");
    printAssembly(raizListaA);
    //printf("d\n");

    return raizListaA;
}