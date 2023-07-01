/* ideia para controlar os registradores em uso:
 * liberar os registradores das atribuições, das menções de vetores,
 * das chamadas de função e parametros
 */

#include "globals.h"
#include "bgen.h"
#include "string.h"
#include "stdlib.h"

instB *raizBinario = NULL;

void decimalToBinary(int dec, int binary[], int tam){

  for (int i = tam - 1; i >= 0; i--){
    if (dec > 0){
      binary[i] = dec % 2;
      dec /= 2;
    }
    else
      binary[i] = 0;
  }
}

void igualaOP(int opBChar[], int bits[]){

  for (int i = 0; i < OP_BITS; i++) opBChar[i] = bits[i];
}

void converteOp (OperacaoA opB, int opBChar[]){
  switch (opB)
  {
    case addA:{
      int auxBits[6] = {0,0,0,0,0,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case addiA:{
      int auxBits[6] = {0,0,0,0,0,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case subA:{
      int auxBits[6] = {0,0,0,0,1,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case subiA:{
      int auxBits[6] = {0,0,0,0,1,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case multA:{
      int auxBits[6] = {0,0,0,1,0,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case multiA:{
      int auxBits[6] = {0,0,0,1,0,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case divA:{
      int auxBits[6] = {0,0,0,1,1,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case diviA:{
      int auxBits[6] = {0,0,0,1,1,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case sltA:{
      int auxBits[6] = {0,0,1,0,0,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case andA:{
      int auxBits[6] = {0,0,1,0,0,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case andiA:{
      int auxBits[6] = {0,0,1,0,1,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case orA:{
      int auxBits[6] = {0,0,1,0,1,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case oriA:{
      int auxBits[6] = {0,0,1,1,0,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case notA:{
      int auxBits[6] = {0,0,1,1,0,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case srA:{
      int auxBits[6] = {0,0,1,1,1,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case slA:{
      int auxBits[6] = {0,0,1,1,1,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case loadA:{
      int auxBits[6] = {0,1,0,0,0,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case loadiA:{
      int auxBits[6] = {0,1,0,0,0,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case storeA:{
      int auxBits[6] = {0,1,0,0,1,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case moveA:{
      int auxBits[6] = {0,1,0,0,1,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case jA:{
      int auxBits[6] = {0,1,0,1,0,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case jrA:{
      int auxBits[6] = {0,1,0,1,0,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case jalA:{
      int auxBits[6] = {0,1,0,1,1,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case beqA:{
      int auxBits[6] = {0,1,0,1,1,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case bneA:{
      int auxBits[6] = {0,1,1,0,0,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case nopA:{
      int auxBits[6] = {0,1,1,0,0,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case haltA:{
      int auxBits[6] = {0,1,1,0,1,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    case inA:{
      int auxBits[6] = {0,1,1,0,1,1};
      igualaOP(opBChar, auxBits);
      break;
    }
    case outA:{
      int auxBits[6] = {0,1,1,1,0,0};
      igualaOP(opBChar, auxBits);
      break;
    }
    default:
      break;
  }
}

void insereBinario (TipoA tipoQuad, OperacaoA opB, int rs, int rt, int rd, int im){
  instB *newNode = (instB *) malloc(sizeof(instB));

  decimalToBinary(im, newNode->im, IM_JUMP_BITS);
  decimalToBinary(rs, newNode->rs, REG_BITS);
  decimalToBinary(rt, newNode->rt, REG_BITS);
  decimalToBinary(rd, newNode->rd, REG_BITS);
  converteOp (opB, newNode->opB);
  newNode->tipoB = tipoQuad;
  newNode->next = NULL;

  if (raizBinario == NULL) raizBinario = newNode;
  else{
    instB *auxNode = raizBinario;
    while (auxNode->next != NULL)
        auxNode = auxNode->next;

    auxNode->next = newNode;
  }
}

void imprimeBinario(instB *currInstB){
  if (currInstB != NULL){
    for(int i = 0; i < OP_BITS; i++) printf("%d", currInstB->opB[i]);printf(":");

    if (currInstB->tipoB == tipoR){
      for(int i = 0; i < REG_BITS; i++) printf("%d", currInstB->rs[i]);printf(":");
      for(int i = 0; i < REG_BITS; i++) printf("%d", currInstB->rt[i]);printf(":");
      for(int i = 0; i < REG_BITS; i++) printf("%d", currInstB->rd[i]);
      printf("11111111111");
    }
    else if (currInstB->tipoB == tipoI){
      for(int i = 0; i < REG_BITS; i++) printf("%d", currInstB->rs[i]);printf(":");
      for(int i = 0; i < REG_BITS; i++) printf("%d", currInstB->rt[i]);printf(":");
      for(int i = 0; i < IM_BITS; i++) printf("%d", currInstB->im[i]);
    }
    else if (currInstB->tipoB == tipoJ){
      for(int i = 0; i < IM_JUMP_BITS; i++) printf("%d", currInstB->im[i]);
    }

    printf("\n");

    imprimeBinario(currInstB->next);
  }
}

instB* binaryGen (instA *assemblyRaiz){
  instA *assemblyAux = assemblyRaiz;
  while (assemblyAux != NULL){
    insereBinario (assemblyAux->tipoInst, assemblyAux->opA, assemblyAux->rs, assemblyAux->rt, assemblyAux->rd, assemblyAux->im);
    assemblyAux = assemblyAux->next;
  }
  imprimeBinario(raizBinario);
  return raizBinario;
}