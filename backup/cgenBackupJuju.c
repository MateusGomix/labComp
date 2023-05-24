
#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"
#include "string.h"
#include "stdlib.h"


int registrador = -1;
int linha =-1;




/* prototype for internal recursive code generator */
void cGen (TreeNode * tree);

/* Procedure genStmt */
static void genStmt( TreeNode * tree)
{ TreeNode * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
  char *p1Composto = "_t", *p2Composto = "_t";
  char *p3Composto = "_t";
  int linhaV=0 , linhaF =0;
  switch (tree->kind.stmt) {

      case IfK :
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         p3 = tree->child[2] ;
         
         

         // condicao do if

         fprintf(listing,"if ");
         cGen(p1);
         
                  
         linha++;
         linhaV=linha;
         fprintf(listing," goto _L%d\n", linhaV);
         
         //bloco falso
         
         
         if(p3!=NULL){// tem else
            cGen(p3);            
         }
         fprintf(listing,"\n");
         linha++;
         linhaF=linha;
         fprintf(listing,"goto _L%d\n", linhaF);

         //bloco verdadeiro
        
         fprintf(listing,"_L%d: ", linhaV);

         cGen(p2);
         fprintf(listing,"\n");

         //proxima instrucao
         fprintf(listing,"_L%d: ", linhaF);

         
         //irmao do no       
         if(tree->sibling!=NULL){
            cGen(tree->sibling);
         }



         break; /* if_k */

      case WhileK:
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
        
         linha++;
         linhaV=linha;
         
         
         // condicao do while
         fprintf(listing,"_L%d: if ", linhaV);
         cGen(p1);
         

         linha++;
         linhaF=linha;
         fprintf(listing," goto _L%d\n", p1Composto, linhaF);
         
         //bloco de repeticao
         
         cGen(p2);
         fprintf(listing,"\n");
         //volta para condicao
         fprintf(listing,"goto _L%d\n ", linhaV);

         //proxima instrucao
         fprintf(listing,"_L%d: ", linhaF);


         
         //irmao do no       
         if(tree->sibling!=NULL){
            cGen(tree->sibling);
         }

         break; /* repeat */

      case RecebeK:
         
         
         p1=tree->child[0];
         p2=tree->child[1];

         
         
         //p1 e var nao vetor

         if(p1->kind.exp == IdK && !strcmp(p1->tipoID,"var") && p1->vetor==0){
            fprintf(listing,"%s = ",tree->child[0]->attr.name);
            cGen(p2);
            fprintf(listing,"\n");
            
         }
         
         //p1 e var vetor
         

         if(p1->kind.exp == IdK && !strcmp(p1->tipoID,"var") && p1->vetor==1){
            
            cGen(p1);
            fprintf(listing," = ",p1Composto);
            cGen(p2);
            fprintf(listing,"\n");
              
         }

               
         if(tree->sibling!=NULL){
           
            cGen(tree->sibling);
         }

         break; /* assign_k */

      case RetornoK:
         p1 = tree->child[0] ;

         fprintf(listing,"return ");      
         cGen(p1);
         fprintf(listing,"\n");

                  
         //irmao do no       
         if(tree->sibling!=NULL){
            cGen(tree->sibling);
         }
         
         break; /* assign_k */
      
      default:
         break;
    }
} /* genStmt */

/* Procedure genExp  */
static void genExp( TreeNode * tree)
{ int loc;
  TreeNode * p1, * p2;
  char *p1Composto = "_t", *p2Composto = "_t";
  switch (tree->kind.exp) {

   case ConstK :

      fprintf(listing,"%d",tree->attr.val); 

      //irmao do no       
         if(tree->sibling!=NULL){
            cGen(tree->sibling);
         }
      
      break; /* ConstK */
    
    case IdK : 

      

      //var nao vetor
      
      if(!strcmp(tree->tipoID,"var")&&tree->vetor==0){    
         
         fprintf(listing,"%s",tree->attr.name); 

      }

      // var vetor

      if(!strcmp(tree->tipoID,"var")&&tree->vetor==1){
         
         p1=tree->child[0];        

         registrador++;         
         fprintf(listing,"_rt%d = 4*",registrador);
         cGen(p1);
         fprintf(listing,"\n");

         char *aux;
         //itoa(registrador,aux,10);
                  
         p1Composto= tree->attr.name;
         strcat(p1Composto,"[_t");                  
         strcat(p1Composto,aux);
         strcat(p1Composto,"]");
         fprintf(listing,"%s",p1Composto);
         fprintf(listing,"\n");


      }
                  


      //fun
      if(!strcmp(tree->tipoID,"fun")){
         p1 = tree->child[0];
         int i;
         for(i=0;i<tree->qtdArgumentos;i++){
            
            fprintf(listing,"param "); 
            cGen(p1); 
            fprintf(listing,"\n");
            p1=p1->sibling;
         }

         registrador++;
         fprintf(listing,"_rt%d = ",registrador);
         fprintf(listing,"call %s, %d\n", tree->attr.name, tree->qtdArgumentos);  
      }

                 
         //irmao do no       
         /*if(tree->sibling!=NULL){
            cGen(tree->sibling);
         }  */

      
      break; /* IdK */

   case OpK : 
         p1 = tree->child[0];
         p2 = tree->child[1];
         
         registrador++;
         fprintf(listing,"_rt%d = ",registrador);

         cGen(p1);               
           

         switch (tree->attr.op) {
            case SOMA :               
               fprintf(listing," + ");
               break;
            case SUB :               
               fprintf(listing," - ");
               break;
            case MULT :              
               fprintf(listing," * ");
               break;
            case DIV :               
               fprintf(listing," / ");
               break;
            case MENOR :
               
               fprintf(listing," < ");
               break;
            case MENORIG :               
               fprintf(listing," <= ");
               break;
            case MAIOR :               
               fprintf(listing," > ");
               break;
            case MAIORIG :               
               fprintf(listing," >= ");
               break;
            case IGUAL :               
               fprintf(listing," == ");
               break;
            default:
               fprintf(listing,"BUG: Unknown operator");
               break;
         
         } /* case op */


         cGen(p2);
         fprintf(listing,"\n");

         //irmao do no       
         if(tree->sibling!=NULL){
            cGen(tree->sibling);
         }

         break; /* OpK */

   case FuncK : 
            
      
      p1= tree->child[1];      

      fprintf(listing,"%s: ", tree->attr.name);

      cGen(p1);
      fprintf(listing,"\n");

      //irmao do no       
      if(tree->sibling!=NULL){
         cGen(tree->sibling);
      }

      break;
    default:
      break;
  }
} /* genExp */


/* Procedure genEsp */
static void genEsp( TreeNode * tree)
{ int loc;
  TreeNode * p1, * p2;
  char *p1Composto = "_t", *p2Composto = "_t";
  switch (tree->kind.esp) {

    case IntK :    
    case VoidK :

    
      p1 = tree->child[0];
      if(p1!=NULL && p1->kind.exp==FuncK){ //funck
         cGen(p1);
      }
      if(tree->sibling!=NULL){ //var
         cGen(tree->sibling);
      }
      
      break; 
   
    default:
      break;
  }
} /* genEsp */




void cGen( TreeNode * tree)
{ if (tree != NULL)
   

  { switch (tree->nodekind) {
      case StmtK:
        genStmt(tree);
        break;
      case ExpK:
        genExp(tree);
        break;
      case EspK:
        genEsp(tree);        
        break;
      default:
        break;
    }
    /* rever */
    /*for(int i; i < MAXCHILDREN; i++)
      if(tree->child[i] != NULL)cGen(tree->child[i]);
      else break;*/
    cGen(tree->sibling);
  }
}
