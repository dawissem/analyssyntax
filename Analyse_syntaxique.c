#include <stdio.h>
#include <string.h>
#define id 1
#define aff 2
#define pv 3
#define plus 5
#define nb 4
#define po 6
#define pf 7
#define eof 8
int Symbole ;
FILE *fp;
char ch[100];
int etat;
char c;
int erreur=0;

void P(){
l_inst();
}

void l_inst(){
I();
L1();
}

void exp(){
if(Symbole==nb){
    accepter(nb);
    E1();
}
else if(Symbole==po){
    accepter(po);
    exp();
    accepter(pf);
    E1();
}
else if(Symbole==id){
        accepter(id);
E1();}

else {printf("nb ou id ou ( ) manquant");erreur=1;}
}
  void E1(){
  if(Symbole==plus){
        accepter(plus);
        exp();
        E1();
  }
  }

void L1 (){
if(Symbole==id)
    l_inst();
    }

    void I(){
    if(Symbole==id){
        accepter(id);
        accepter(aff);
        exp();
        accepter(pv);

    }
    else{ printf("id manquant");
    erreur=1;}

    }


int analec()
{
    int etat=0;


    while(1)
    {

      switch (etat)
      {
          case 0: c = fgetc(fp);

          if ((c==' ')||(c=='\t')||(c=='\n') )
          {
              etat = 0;
              break;
          }

         else if (isalpha(c))
          {
              etat = 1;
              break;
          }
          else if (isdigit(c))
          {
              etat = 3;
              break;
          }
          else if (c == ';')
          {
              etat = 5;
              break;
          }
          else if (c == '+')
          {
              etat = 6;
              break;
          }
          else if (c == '(')
          {
              etat = 7;
              break;
          }
          else if (c == ')')
          {
              etat = 8;
              break;
          }
          else if (c == EOF)
          {
              etat = 9;
              break;
          }
          else if(c==':'){
            etat=10 ;
            break;
          }


          case 1: c = fgetc(fp);

          if (isdigit(c) || isalpha(c))
          {
              etat = 1;
              break;
          }
          else
          {
              etat = 2;
              break;
          }

          case 2: fseek(fp, -1, SEEK_CUR);
              return (id);

          case 3: c = fgetc(fp);
          if (isdigit(c))
          {
              etat = 3;
              break;
          }
          else
          {
              etat = 4;
              break;
          }
          case 4: fseek(fp, -1, SEEK_CUR);
              return (nb);

          case 5: return(pv);
          case 6: return(plus);
          case 7: return(po);
          case 8: return(pf);
           case 9: return(EOF);
            case 10:  c = fgetc(fp);
            if(c=="="){
                etat=11;break;
            }
            case 11 : return(aff);
      }
    }
}
//©All copyrights by MANAI.wissem
  void accepter(int t) {
    // Vérifie si Symbole est égal à t
    if (Symbole == t) {
        Symbole = analec();
    } else {
        // Si Symbole n'est pas égal à t, affiche un message d'erreur en fonction de t
        switch (t) {
            case 1: printf("id manquant"); break;
            case 2: printf(":= manquant "); break;
            case 3: printf("; manquant "); break;
            case 4: printf("nb  "); break;
            case 5: printf("+ manquant "); break;
            case 6: printf("( manquant "); break;
            case 7: printf(") manquant "); break;


        }
    }
}


int main()
{
    printf("donner le chemin pour votre fichier\n");
    scanf("%s", ch);
    fp = fopen(ch, "r");
    Symbole = analec();
    P();
    if (erreur){printf("prgm analysé avec erreur");
    }
    else printf("prgm accepté");
    }
