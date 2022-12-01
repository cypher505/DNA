#include"DATA_struct.h"


duo_chaine* creer_duo_chaine(char*x, char* y, int n, int m){
    duo_chaine* res = (duo_chaine*) malloc ( sizeof(duo_chaine) );
    if(res ==NULL){
        printf("Ereur d'allocation\n");
        return NULL;
    }
    res->x = x;
    res->y = y;
    res->x[n]='\0';
    res->y[m]='\0';
    res->n = n;
    res->m = m;
    return res;
}

void supprimer_duo_chaine(duo_chaine* duo){
    free(duo->x);
    free(duo->y);
    free(duo);

}

void afficher_duo_chaine(duo_chaine* duo){
    printf("n= %d, m= %d\n x= %s \n y= %s \n",duo->n,duo->m,duo->x,duo->y);
}

Align* creer_alignement(int n, int m){
    Align* res = (Align*) malloc (sizeof(Align));
    char* x =(char*) malloc( (n+m+1) * sizeof(char));
    char* y=(char*) malloc ( (n+m+1) * sizeof(char));
    for(int i=0;i<n+m;i++){
        x[i]='|';
        y[i]='|';
    }
    x[n+m]='\0';
    y[n+m]='\0';
    res->x = x;
    res->y = y;
    res->iter=n+m;
    res->dist=0;
    res->size = n + m;
    return res;
}


void afficher_alignement(Align* algn){
    if(algn==NULL ||algn->x==NULL || algn->y==NULL ){
        printf("Algn est = NULL");
        return;
    }

    printf("%s",algn->x);
    printf("\n");
    printf("%s",algn->y);

    printf("\nDistance d'édition = %d\n",algn->dist);
}

void supprimer_alignement(Align* algn){
    free(algn->x);
    free(algn->y);
    free(algn);
}

void check_sanity(Align* res,duo_chaine *duo){
    deletechar(res->x,'-');
    deletechar(res->y,'-');
    if (strcmp(res->x,duo->x)   ||   strcmp(res->y,duo->y)){
        printf("x or y does not match \n");
        return;
    }
    printf("sanity check : good\n");
}



//delet all recurence of char c in the string s
void deletechar(char *s,char c){
	int i,k=0;
    
    for(i=0;i<strlen(s);i++)
    {
     	s[i]=s[i+k];
 
     	if(s[i]==c){
		  k++;
		  i--;
	    }
    
    }
	   
}