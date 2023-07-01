/****************************************************/
/* File: agen.h                                     */
/* The code generator interface to the TINY compiler*/
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _BGEN_H_
#define _BGEN_H_

#include "agen.h"
#include "bgen.h"

#define REG_BITS 5
#define IM_BITS 16
#define IM_JUMP_BITS 26
#define OP_BITS 6

typedef struct instrucaoBinario{
    int opB[OP_BITS], rs[REG_BITS],rt[REG_BITS],rd[REG_BITS],im[IM_JUMP_BITS];
    TipoA tipoB;
    struct instrucaoBinario *next;
}instB;

instB* binaryGen(instA *);

#endif
