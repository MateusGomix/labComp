/****************************************************/
/* File: agen.h                                     */
/* The code generator interface to the TINY compiler*/
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _AGEN_H_
#define _AGEN_H_

#include "cgen.h"

/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void assemblyGen(rStruct *);

typedef enum {tipoR,tipoI,tipoJ} TipoA;
typedef enum {addA,addiA,subA,subiA,multA,multiA,divA,diviA,sltA,andA,andiA,orA,oriA,notA,
              srA,slA,loadA,loadiA,storeA,moveA,jA,jrA,jalA,beqA,bneA,nopA,haltA,inA,outA} InstrucaoA;

typedef struct instrucaoAssembly{
    TipoA tipoInst;
    InstrucaoA inst;
    int rs,rt,rd,im;
    int line;
    struct instrucaoAssembly *next;
}instA;

#endif
