/****************************************************/
/* File: agen.h                                     */
/* The code generator interface to the TINY compiler*/
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _AGEN_H_
#define _AGEN_H_

#include "cgen.h"

#define TOTAL_REGS 29

/* add uma propriedade arg para verificar se é necessário usar endereço de memória de vetor */
typedef struct VarListRec
   { int memloc;
     int tam;
     char *name;
     int isVetArg;
     struct VarListRec * next;
   } * VarList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
   { char * name;
     int lineno;
     //int calling; /* if calling function */
     VarList vars;
     struct BucketListRec * next;
   } * BucketList;

/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void assemblyGen(rStruct *);

typedef enum {tipoR,tipoI,tipoJ} TipoA;
typedef enum {addA,addiA,subA,subiA,multA,multiA,divA,diviA,sltA,andA,andiA,orA,oriA,notA,
              srA,slA,loadA,loadiA,storeA,moveA,jA,jrA,jalA,beqA,bneA,nopA,haltA,inA,outA} OperacaoA;

typedef struct instrucaoAssembly{
    TipoA tipoInst;
    OperacaoA opA;
    int rs,rt,rd,im;
    int line;
    struct instrucaoAssembly *next;
}instA;

/* TENTANDO FAZER MINHA PILHA */
typedef struct ItemReg{
	int *regsEmpilhados;
	struct ItemReg *prox;
} TItemReg;

typedef struct PilhaReg {
  int tam;
  struct ItemReg *topo;
} TPilhaReg;

TPilhaReg* criaPilhaReg();

TItemReg* criaItemReg(int*);

void addPilhaReg(TPilhaReg*, int*);

int* popPilhaReg(TPilhaReg*);

#endif
