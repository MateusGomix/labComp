#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include <string.h>

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

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc , char * type, char * escopo, char * tipoID, int qtd, int vet, TreeNode *no)
{ char * fusao = (char *) malloc(sizeof(char));
  strcpy(fusao,name);
  strcat(fusao,escopo);
  int h = hash(fusao);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) /* variable not yet in table */
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->type = type;
    l->escopo = escopo;
    l->argumentos = qtd;
    l->vetor = vet;
    l->tipoID = tipoID;
    l->no = no;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->lines->next = NULL;
    l->next = hashTable[h];
    hashTable[h] = l; }
  else /* found in table, so just add line number */
  { no->vetor = l->vetor; //recupera se é vetor na hora da inserção
    LineList t = l->lines;
    while (t->next != NULL) t = t->next;
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name, char * escopo )
{ char * fusao = (char *) malloc(sizeof(char));
  strcpy(fusao,name);
  strcat(fusao,escopo);
  int h = hash(fusao);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) return -1;
  else return l->memloc;
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing)
{ int i;
  fprintf(listing,"Nome da Variavel   Tipo(dado)   Tipo(ID)     Escopo      Linhas\n");
  fprintf(listing,"----------------    --------    --------    --------   ------------\n");
  for (i=0;i<SIZE;++i)
  { if (hashTable[i] != NULL)
    { BucketList l = hashTable[i];
      while (l != NULL)
      { LineList t = l->lines;
        fprintf(listing,"%-21s ",l->name);
        fprintf(listing,"%-11s ",l->type);
        fprintf(listing,"%-11s ",l->tipoID);
        fprintf(listing,"%-10s ",l->escopo);
        while (t != NULL)
        { fprintf(listing,"%4d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
} /* printSymTab */

char* retornaTipoFuncK(char *nome){
  char * fusao = (char *) malloc(sizeof(char));
  strcpy(fusao,nome);
  strcat(fusao,"\0");
  int h = hash(fusao);
  BucketList l =  hashTable[h];

  return l->type;
}

int retornaArgsFuncK(char *nome){
  char * fusao = (char *) malloc(sizeof(char));
  strcpy(fusao,nome);
  strcat(fusao,"\0");
  int h = hash(fusao);
  BucketList l =  hashTable[h];

  return l->argumentos;
}

int retornaVet(char *nome, char *escopo){
  char * fusao = (char *) malloc(sizeof(char));
  strcpy(fusao,nome);
  strcat(fusao,escopo);
  int h = hash(fusao);
  BucketList l =  hashTable[h];

  return l->vetor;
}

TreeNode* retornaNo(char *nome, char *escopo){
  char * fusao = (char *) malloc(sizeof(char));
  strcpy(fusao,nome);
  strcat(fusao,escopo);
  int h = hash(fusao);
  BucketList l =  hashTable[h];

  return l->no;
}