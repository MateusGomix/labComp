%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static char * savedName2; /* Variáveis */
static char * savedName3; /* Funções */
static int savedNum;  /* Salva o número de um token NUM */
static int savedLineNo;  /* ditto */
static int savedLineNo2;  /* Salvas as linhas só para declaração de função */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex(void);
int yyerror(char * message);
PPilha pilhinha = NULL;

%}

%token IF ELSE INT RETURN VOID WHILE
%token ID NUM 
%left SOMA SUB
%left MULT DIV
%left MENOR MENORIG MAIOR MAIORIG IGUAL DIFERENTE 
%token RECEBE
%token PONTOVIR VIRGULA 
%token ABREPAR FECHAPAR ABRECOL FECHACOL ABRECHAVE FECHACHAVE

%token ERROR

%%

programa            : declaracao_lista {
                        savedTree = $1;
                      }
                    ;

declaracao_lista    : declaracao_lista declaracao {
                        YYSTYPE t = $1;
                        //t = t->child[0];
                        if (t != NULL)
                        { while (t->child[0]->sibling != NULL)
                              t = t->child[0]->sibling;
                          t->child[0]->sibling = $2;
                          $$ = $1; }
                        else $$ = $2;
                      }
                    | declaracao {
                        $$ = $1;
                    }
                    ;

declaracao          : var_declaracao {
                        $$ = $1;
                    }
                    | fun_declaracao {
                        $$ = $1;
                    }
                    ;

var_declaracao      : tipo_especificador ID {savedName2 = copyString(ID_tokenString);
                          savedLineNo = lineno;}
                      PONTOVIR {
                        $$ = $1; 
                        YYSTYPE t = newExpNode(IdK);
                        $$->child[0] = t;
                        t->attr.name = savedName2;
                        t->lineno = savedLineNo;
                        t->tipoID = "var";
                        t->declaracao = 1;
                      }
                    | tipo_especificador ID {savedName2 = copyString(ID_tokenString);
                          savedLineNo = lineno;} ABRECOL NUM {savedNum = atoi(tokenString);} FECHACOL PONTOVIR {
                        $$ = $1;
                        YYSTYPE t = newExpNode(IdK);
                        t->attr.name = savedName2;
                        t->lineno = savedLineNo;
                        t->tipoID = "var";
                        t->declaracao = 1;
                        $$->child[0] = t;
                        YYSTYPE t2 = newExpNode(ConstK);
                        t2->attr.val = savedNum;
                        t->child[0] = t2;
                        t->vetor = 1;
                    }
                    ;

tipo_especificador  : INT {
                        $$ = newEspNode(IntK);
                      }
                    | VOID  {
                      $$ = newEspNode(VoidK);
                    }
                    ;

fun_declaracao      : tipo_especificador ID {savedName3 = copyString(ID_tokenString);
                          savedLineNo2 = lineno;} ABREPAR params FECHAPAR composto_decl {
                        $$ = $1; 
                        YYSTYPE t = newExpNode(FuncK);
                        $$->child[0] = t;
                        t->child[0] = $5;
                        t->child[1] = $7;
                        t->attr.name = savedName3;
                        t->lineno = savedLineNo2;
                        t->tipoID = "fun";
                        t->declaracao = 1;
                      }
                    ;

params              : param_lista {
                        $$ = $1;
                      }
                    | VOID {
                      $$ = NULL;
                    }
                    ;

param_lista         : param_lista VIRGULA param {
                        YYSTYPE t = $1;
                        if (t != NULL)
                        { while (t->sibling != NULL)
                              t = t->sibling;
                          t->sibling = $3;
                          $$ = $1; }
                          else $$ = $3;
                      }
                    | param {
                      $$ = $1;
                    }
                    ;

param               : tipo_especificador ID {
                        $$ = $1;
                        YYSTYPE t = newExpNode(IdK);
                        t->attr.name = copyString(ID_tokenString);
                        t->lineno = lineno;
                        t->tipoID = "var";
                        t->declaracao = 1;
                        t->isArg = 1;
                        $$->child[0] = t;
                      }
                    | tipo_especificador ID {savedName2 = copyString(ID_tokenString);
                          savedLineNo = lineno;} ABRECOL FECHACOL {
                      $$ = $1;
                      YYSTYPE t = newExpNode(IdK);
                      t->attr.name = savedName2;
                      t->lineno = savedLineNo;
                      t->tipoID = "var";
                      t->declaracao = 1;
                      t->isArg = 1;
                      $$->child[0] = t;
                      t->vetor = 1;
                    }
                    ;

composto_decl       : ABRECHAVE local_declaracoes statement_lista FECHACHAVE {
                        YYSTYPE t = $2;
                        if (t != NULL) {
                          $$ = $2;
                          if($$->sibling == NULL) $$->sibling = $3;
                          else{ 
                            YYSTYPE aux = t;
                            while (aux->sibling != NULL)
                              aux = aux->sibling;
                            aux->sibling = $3;
                          }
                        }
                        else{
                          $$=$3;
                        }
                      }
                    ;

local_declaracoes   : local_declaracoes var_declaracao {
                        YYSTYPE t = $1;
                        if (t != NULL)
                        { while (t->sibling != NULL)
                              t = t->sibling;
                          t->sibling = $2;
                          $$ = $1; }
                          else $$ = $2;
                      }
                    | {
                      $$ = NULL;
                    }
                    ;

statement_lista     : statement_lista statement {
                        YYSTYPE t = $1;
                        if (t != NULL)
                        { while (t->sibling != NULL)
                              t = t->sibling;
                          t->sibling = $2;
                          $$ = $1; }
                          else $$ = $2;
                      }
                    | {
                      $$ = NULL;
                    }
                    ;

statement           : expressao_decl  {
                        $$ = $1;
                    }
                    | composto_decl {
                        $$ = $1;
                    }
                    | selecao_decl  {
                        $$ = $1;
                    }
                    | iteracao_decl {
                        $$ = $1;
                    }
                    | retorno_decl  {
                        $$ = $1;
                    }
                    ;

expressao_decl      : expressao PONTOVIR  {
                        $$ = $1;
                      }
                    | PONTOVIR  {
                      $$ = NULL;
                    }
                    ;

selecao_decl        : IF ABREPAR expressao FECHAPAR statement {
                        $$ = newStmtNode(IfK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                      }
                    | IF ABREPAR expressao FECHAPAR statement ELSE statement {
                      $$ = newStmtNode(IfK);
                      $$->child[0] = $3;
                      $$->child[1] = $5;
                      $$->child[2] = $7;
                    }
                    ;

iteracao_decl       : WHILE ABREPAR expressao FECHAPAR statement  {
                        $$ = newStmtNode(WhileK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                      }
                    ;

retorno_decl        : RETURN PONTOVIR {
                        $$ = newStmtNode(RetornoK);
                        $$->attr.op = RETURN;
                      }
                    | RETURN expressao PONTOVIR {
                        $$ = newStmtNode(RetornoK);
                        $$->attr.op = RETURN;
                        $$->child[0] = $2;
                    }
                    ;

expressao           : var RECEBE expressao  {
                        $$ = newStmtNode(RecebeK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                      }
                    | simples_expressao {
                        $$ = $1;
                    }
                    ;

var                 : ID  {
                            $$ = newExpNode(IdK);
                            $$->attr.name = copyString(ID_tokenString);
                            $$->lineno = lineno;
                            $$->tipoID = "var";
                          }
                    | ID {savedName2 = copyString(ID_tokenString);
                          savedLineNo = lineno;} 
                      ABRECOL expressao FECHACOL {
                        $$ = newExpNode(IdK);
                        $$->child[0] = $4;
                        $$->attr.name = savedName2;
                        $$->lineno = savedLineNo;
                        $$->tipoID = "var";
                      }
                    ;

simples_expressao   : soma_expressao relacional soma_expressao  {
                        $$ = $2;
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                      }
                    | soma_expressao  {
                      $$ = $1;
                    }
                    ;

relacional          : MENORIG {
                        $$ = newExpNode(OpK);
                        $$->attr.op = MENORIG;
                      }
                    | MENOR {
                        $$ = newExpNode(OpK);
                        $$->attr.op = MENOR;
                      }
                    | MAIOR {
                        $$ = newExpNode(OpK);
                        $$->attr.op = MAIOR;
                      }
                    | MAIORIG {
                        $$ = newExpNode(OpK);
                        $$->attr.op = MAIORIG;
                      }
                    | IGUAL {
                        $$ = newExpNode(OpK);
                        $$->attr.op = IGUAL;
                      }
                    | DIFERENTE {
                        $$ = newExpNode(OpK);
                        $$->attr.op = DIFERENTE;
                      }
                    ;

soma_expressao      : soma_expressao soma termo {
                        $$ = $2;
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                      }
                    | termo {
                      $$ = $1;
                    }
                    ;

soma                : SOMA  {
                        $$ = newExpNode(OpK);
                        $$->attr.op = SOMA;
                      }
                    | SUB {
                        $$ = newExpNode(OpK);
                        $$->attr.op = SUB;
                      }
                    ;

termo               : termo mult fator  {
                        $$ = $2;
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                      }
                    | fator {
                      $$ = $1;
                    }
                    ;

mult                : MULT  {
                        $$ = newExpNode(OpK);
                        $$->attr.op = MULT;
                      }
                    | DIV {
                        $$ = newExpNode(OpK);
                        $$->attr.op = DIV;
                      }
                    ;

fator               : ABREPAR expressao FECHAPAR  {
                        $$ = $2;
                      }
                    | var {
                      $$ = $1;
                    }
                    | ativacao  {
                      $$ = $1;
                    }
                    | NUM {
                      $$ = newExpNode(ConstK);
                      $$->attr.val = atoi(tokenString);
                    }
                    ;

ativacao            : ID {if(pilhinha == NULL) pilhinha = criaPilha(); addPilha(pilhinha,copyString(ID_tokenString));
                          savedLineNo = lineno;} ABREPAR args FECHAPAR  {
                        $$ = newExpNode(IdK);
                        $$->attr.name = popPilha(pilhinha);
                        $$->lineno = savedLineNo;
                        $$->tipoID = "fun";
                        $$->child[0] = $4;
                        if(strcmp($$->attr.name,"input") == 0 || strcmp($$->attr.name,"output") == 0) $$->declaracao = 1;
                      }
                    ;

args                : arg_lista {
                        $$ = $1;
                      }
                    | {
                      $$ = NULL;
                    }
                    ;

arg_lista           : arg_lista VIRGULA expressao {
                        YYSTYPE t = $1;
                        if (t != NULL)
                        { while (t->sibling != NULL)
                              t = t->sibling;
                          t->sibling = $3;
                          $$ = $1; }
                          else $$ = $3;
                      }
                    | expressao {
                      $$ = $1;
                    }
                    ;

%%

int yyerror(char * message)
{ if(Error) return 0;
  fprintf(listing,"ERRO SINTATICO: ");
  printToken(yychar,"\0");
  fprintf(listing," LINHA: %d\n",lineno);
  Error = TRUE;
  return 0;
}

static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}