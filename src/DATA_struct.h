#ifndef DATA_struct_H
#define DATA_struct_H
#define INF 1e9
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>


typedef struct _duo_chaine{
    char* x;
    char* y;
    int n;
    int m;
} duo_chaine;

/*Creation d'un duo*/
duo_chaine* creer_duo_chaine(char*x, char* y, int n, int m);

//free the space of an duo
void supprimer_duo_chaine(duo_chaine* duo);

//print an duo
void afficher_duo_chaine(duo_chaine* duo);

// alignements de genome
typedef struct _Align{
    char* x;
    char* y;
    int size ; //longeur de la chaine;
    int dist ; // distance edition
    int iter; 
}Align ;


/*Creation d'un Align*/
Align* creer_alignement(int n, int m);

//free the space of an Align
void supprimer_alignement(Align* algn);


//print an Align
void afficher_alignement(Align* algn);

//preforms a sanity check on the alignment res of the duo 
//(check wether the x and y from the alignment is eqyal to the x and y of the duo)
void check_sanity(Align* res,duo_chaine *duo);


//delete all recurence of c in string s 
void deletechar(char *s,char c);

#endif