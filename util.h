/****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType, const char* );

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind);

/* Function newEspNode creates a new especification 
 * node for syntax tree construction
 */
TreeNode * newEspNode(EspKind);

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );

#endif

/* TENTANDO FAZER MINHA PILHA */
typedef struct Item *PItem;

typedef struct Item{
	char *nome;
	PItem prox;
} TItem;

typedef struct Pilha *PPilha;

typedef struct Pilha {
  int tam;
  PItem topo;
} TPilha;

PPilha criaPilha();

PItem criaItem(char *);

void addPilha(PPilha, char *);

char* popPilha(PPilha);