#include "globals.h"
#include "util.h"
#include "string.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case IF: fprintf(listing,"IF"); if(strcmp(tokenString, "\0") != 0) fprintf(listing,": %s\n",tokenString); break;
    case ELSE: fprintf(listing,"ELSE"); if(strcmp(tokenString, "\0") != 0) fprintf(listing,": %s\n",tokenString); break;
    case INT: fprintf(listing,"INT"); if(strcmp(tokenString, "\0") != 0) fprintf(listing,": %s\n",tokenString); break;
    case RETURN: fprintf(listing,"RETURN"); if(strcmp(tokenString, "\0") != 0) fprintf(listing,": %s\n",tokenString); break;
    case VOID: fprintf(listing,"VOID"); if(strcmp(tokenString, "\0") != 0) fprintf(listing,": %s\n",tokenString); break;
    case WHILE: fprintf(listing,"WHILE"); if(strcmp(tokenString, "\0") != 0) fprintf(listing,": %s\n",tokenString); break;
    case SOMA: if(strcmp(tokenString, "\0") != 0) fprintf(listing,"SOMA: +\n"); else fprintf(listing,"+"); break;
    case SUB:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"SUB: -\n"); else fprintf(listing,"-"); break;
    case MULT:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"MULT: *\n"); else fprintf(listing,"*"); break;
    case DIV:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"DIV: /\n"); else fprintf(listing,"/"); break;
    case MENOR:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"MENOR: <\n"); else fprintf(listing,"<"); break;
    case MENORIG:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"MENORIG: <=\n"); else fprintf(listing,"<="); break;
    case MAIOR:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"MAIOR: >\n"); else fprintf(listing,">"); break;
    case MAIORIG:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"MAIORIG: >=\n"); else fprintf(listing,">="); break;
    case IGUAL:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"IGUAL: ==\n"); else fprintf(listing,"=="); break;
    case DIFERENTE:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"DIFERENTE: !=\n"); else fprintf(listing,"!="); break;
    case RECEBE:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"RECEBE: =\n"); else fprintf(listing,"="); break;
    case PONTOVIR:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"PONTOVIR: ;\n"); else fprintf(listing,";"); break;
    case VIRGULA:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"VIRGULA: ,\n"); else fprintf(listing,","); break;
    case ABREPAR:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"ABREPAR: (\n"); else fprintf(listing,"("); break;
    case FECHAPAR:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"FECHAPAR: )\n"); else fprintf(listing,")"); break;
    case ABRECOL:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"ABRECOL: [\n"); else fprintf(listing,"["); break;
    case FECHACOL:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"FECHACOL: ]\n"); else fprintf(listing,"]"); break;
    case ABRECHAVE:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"ABRECHAVE: {\n"); else fprintf(listing,"{"); break;
    case FECHACHAVE:  if(strcmp(tokenString, "\0") != 0) fprintf(listing,"FECHACHAVE: }\n"); else fprintf(listing,"}"); break;
    case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUM:
      fprintf(listing,
          "NUM, valor = %s\n",tokenString);
      break;
    case ID:
      fprintf(listing,
          "ID, nome = %s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "ERRO LEXICO: %s LINHA: %d\n",tokenString, lineno);
          Error = TRUE;
      break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
    t->tipoID = "\0";
    t->declaracao = 0;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
    t->tipoID = "\0";
    t->declaracao = 0;
    t->vetor = 0;
    t->qtdArgumentos = 0;
    t->isArg = 0;
  }
  return t;
}

/* Function newEspNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newEspNode(EspKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = EspK;
    t->kind.esp = kind;
    t->lineno = lineno;
    t->tipoID = "\0";
    t->declaracao = 0;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n*sizeof(char));
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"if\n");
          break;
        case WhileK:
          fprintf(listing,"while\n");
          break;
        case RecebeK:
          fprintf(listing,"=\n");
          break;
        case RetornoK:
          fprintf(listing,"return\n");
          break;
        default:
          fprintf(listing,"Unknown StmtNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { char * tipo;switch (tree->kind.exp) {
        case OpK:
          printToken(tree->attr.op,"\0");
          fprintf(listing,"\n");
          break;
        case ConstK:
          fprintf(listing,"%d\n",tree->attr.val);
          break;
        case IdK:
          if(tree->vetor) fprintf(listing,"%s[]\n",tree->attr.name);
          else fprintf(listing,"%s\n",tree->attr.name);
          break;
        case FuncK:
          fprintf(listing,"%s\n",tree->attr.name);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==EspK)
    { switch (tree->kind.esp) {
        case IntK:
          fprintf(listing,"int\n");
          break;
        case VoidK:
          fprintf(listing,"void\n");
          break;
        default:
          fprintf(listing,"Unknown EspNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}

/* Pilha implementadas para tratar chamadas de 
 * função dentro de argumentos de ativações */

PPilha criaPilha(){
  PPilha pilha = malloc(sizeof(TPilha));
  pilha->tam = 0;
  pilha->topo = NULL;
  return pilha;
}

PItem criaItem(char *elem){
  PItem item = malloc(sizeof(TItem));
  item->nome = elem;
  item->prox = NULL;
  return item;
}

void addPilha(PPilha pilha, char *elem){
  PItem aux = criaItem(elem);
  
  if(pilha->tam == 0){
    pilha->topo = aux;
  }
  else{
    aux->prox = pilha->topo;
    pilha->topo = aux;
  }
  pilha->tam += 1;
}

char* popPilha(PPilha pilha){
  PItem aux = pilha->topo;
  pilha->topo = aux->prox;
  pilha->tam -= 1;
  return aux->nome;
}