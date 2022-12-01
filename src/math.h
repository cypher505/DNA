#ifndef math
#define math
#include <assert.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#define INF 1e9
#include"../src/DATA_struct.h"

#define C_DEL 2                     //Cout de suppression
#define C_INS 2                     //Cout d'insertion
#define C_SUB_CONCORDANT 3          //Cout de substitution si les lettres son concordantes
#define C_SUB_NON_CONCORDANT 4      //Cout de substitution si les lettres son non concordante
#define min(a,b) (a<=b?a:b)         //min def
#define max(a,b) (a>=b?a:b)         // max def

// returns true (1) if a and b are concordantes letters for the alphabet {ACTG}
int lettres_concordantes(char a, char b);

//return the cost(cout) of changing letters a ans b 
int cout_substitution(char a, char b);

//return min of the thre int a,b,c
int min3(int a, int b, int c);

/*It recursively calculates the cost of the best alignment of (x,y) 
 i an index in [0:x.size()], j an index in [0:y.size()],
 c the cost of aligning (x[0;i],y[0;j])*/
int dist_naif_rec(char* x,char* y,int i, int j, int c, int dist);

//naive function that returnd distance (x,y)
int dist_naif(char* x,char* y);

/*Fonction qui calcule la distance d'édition entre x et y de taille n et m en utilisant un tableau de taille n x m également passé en paramètres*/
int dist_1(char* x, char* y, int ** DP);

/*Fonction retournant l'Align de coût minimum de x et y deux mots de taille m et d'un tableau de distances d'édition préalablement rempli*/
Align* sol_1(char* x, char* y, int** DP);

/*Calculates the distance d'édition between x and y of size n and m 
using an array of size 2*m to improve the spatial complexity of the solution by dynamic programming.*/
int Dist_2(char* x,char* y,int n,int m,int** DP);

//print Matrice
void pM(int **D,int n,int m);

//calculates the optimal Alignment of the duo passed in parameters
Align* PROG_DYN(duo_chaine* duo);

//returns a string with k gaps (-)
char* mot_gaps(int k);

/*function that Align a letter x with the string y containing m letters*/
Align* align_lettre_mot(char x, char* y, int m);

/*Ffunction finding the optimal index where to cut y 
using dynamic programming with Dist and I passed as parameters.*/
int coupure(char * x, char* y,int n,int m,int** DP, int ** I);

// test the coupur fonction on the instance givven int the project example
int test_coup(duo_chaine* duo);

/*returns the optimal alignment using the algorithm devide and conquer (recursive)
we pass Dist and I in parameters so we dont have 
to allocat them every recursive call*/
Align * SOL_2(char * x, char* y,int n,int m, int** Dist, int** I);

//calculates the optimal Alignment of the duo passed in parameters using SOL_2
Align* PROG_DYN_SOL2(duo_chaine* duo);

//calculates the real cost of an allignment
//we use it to test our solutions and see if the corespond to the optimal Distance
int calcul_cout(Align* res);

#endif