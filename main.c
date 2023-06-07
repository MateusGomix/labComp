/* Projeto final da UC: Compiladores 
 * Por: Júlia Sá e Mateus Gomes 
 */

#include "globals.h"

/* Se NO_PARSE TRUE apenas análise léxica */
#define NO_PARSE FALSE
/* se NO_ANALYZE TRUE apenas análise sintátita */
#define NO_ANALYZE FALSE

/* Se NO_CODE TRUE apenas análise semântica */
#define NO_CODE FALSE

#include "util.h"

#if !NO_ANALYZE
#include "analyze.h"
#if !NO_CODE
#include "cgen.h"
#endif
#endif

/* Variáveis globais de linhas e arquivos */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* Se FALSE não imprime o que se refere */
int EchoSource = FALSE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;
int TraceCode = TRUE;

int Error = FALSE;

int main( int argc, char * argv[] )
{ TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".txt");
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nCOMPILACAO C-: %s\n",pgm);
#if NO_PARSE
  while (getToken()!=ENDFILE);
#else
  fprintf(listing,"\nTokens e lexemas:\n");
  syntaxTree = parse();
  if (TraceParse && !Error) {
    fprintf(listing,"\nArvore Sintatica:\n");
    printTree(syntaxTree);
  }
  //printf("saiu da arvore\n");
  salvaEscopo(syntaxTree);
  //printf("saiu do salva escopo\n");
  // ERRO 6
  if(qtdMain == 0 && !Error){
    Error = 1;
    fprintf(listing,"\nERRO SEMANTICO: main LINHA: ???\n");
  }
#if !NO_ANALYZE
  if (! Error)
  { 
    typeCheck(syntaxTree);
    //printf("saiu do typecheck\n");
    buildSymtab(syntaxTree);
    //printf("saiu do buildsymtab\n");
  }

#if !NO_CODE
  if (! Error)
  {
    fprintf(listing,"\nCodigo intermediario:\n");
    
    codeGen(syntaxTree);
  }
#endif
#endif
#endif
  fclose(source);
  return 0;
}