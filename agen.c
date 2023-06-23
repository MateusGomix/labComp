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

#define STRING_TAM 10
#define INT_MEM_BYTES 32
#define TOTAL_REGS 50

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

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
   { char * name;
     char * type;
     char * escopo;
     char * tipoID;
     int argumentos;
     int vetor;
     TreeNode *no;
     LineList lines;
     int memloc ; /* memory location for variable */
     struct BucketListRec * next;
   } * BucketList;

/* the hash table */
static BucketList hashTable[SIZE];

/* prototype for internal recursive code generator */
void aGen(Quad *currQuad);

void aGen(Quad *currQuad){
    switch (currQuad->op)
    {
    case add:
        break;
    
    default:
        break;
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
    Quad *quadAux = interAux->raiz;

    aGen(quadAux);
    
}