/****************************************************/
/* File: cgen.h                                     */
/* The code generator interface to the TINY compiler*/
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _CGEN_H_
#define _CGEN_H_

/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void cGen(TreeNode *);

void codeGen(TreeNode *);

typedef enum {add,sub,mult,divOp,gt,gte,lt,lte,and,or,not,load,store,move,jump,eq,nop,halt,in,out,
              call,arg,lab,fun,end,aloc,param,gotolab,ret,iffalse,assign} Operacao; 

typedef enum {Reg,Const,String} TipoEnd;

typedef struct{
    TipoEnd tipo;
    union{
        int val;
        char *nome;
    }conteudo;
    int regPos;
} Endereco;

typedef struct ListaQuadItem{
    //int location;
    Operacao op;
    Endereco *end1, *end2, *end3;
    struct ListaQuadItem *next;
}Quad;

#endif
