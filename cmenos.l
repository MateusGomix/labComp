%{
#include "globals.h"
#include "util.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
char ID_tokenString[MAXTOKENLEN+1];
%}

DIGITO [0-9]
LETRA [a-zA-Z]
ESPACO [ ]
TAB [\t]
%option noyywrap
%%

"\n"                {++lineno;}
"else"              {return ELSE;}
"if"                {return IF;}
"int"               {return INT;}
"return"            {return RETURN;}
"void"              {return VOID;}
"while"             {return WHILE;}
"/*"                { char c = '\0', d;
                      do
                      { d = c;
                        c = input();
                        if (c == EOF) break;
                        if (c == '\n') lineno++;
                        if (c == '*' && d == '/') return ERROR;
                      } while (c != '/' || d != '*');
                    }
"+"                 {return SOMA;}
"-"                 {return SUB;}
"*"                 {return MULT;}
"/"                 {return DIV;}
"<"                 {return MENOR;}
"<="                {return MENORIG;}
">"                 {return MAIOR;}
">="                {return MAIORIG;}
"=="                {return IGUAL;}
"!="                {return DIFERENTE;}
"="                 {return RECEBE;}
";"                 {return PONTOVIR;}
","                 {return VIRGULA;}
"("                 {return ABREPAR;}
")"                 {return FECHAPAR;}
"["                 {return ABRECOL;}
"]"                 {return FECHACOL;}
"{"                 {return ABRECHAVE;}
"}"                 {return FECHACHAVE;}
{LETRA}+            {strncpy(ID_tokenString,yytext,MAXTOKENLEN);return ID;}
{LETRA}+{DIGITO}+   {return ERROR;}
{DIGITO}+           {return NUM;}
{ESPACO}+|{TAB}+    {}
.                   {return ERROR;}

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}