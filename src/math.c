#include "math.h"

int lettres_concordantes(char a, char b){
    // returns true (1) if a and b are concordant letters for the alphabet {ACTG}
    
    switch (a){
    case 'A':
        if (b=='T')return 1;
        else return 0;
        break;

    case 'C':
        if (b=='G')return 1;
        else return 0;
        break;

    case 'T':
        if (b=='A') return 1;    
        else return 0;
        break;

    case 'G':
        if (b=='C')return 1;
        else return 0;
        break;
    }
    return -1;

}




int cout_substitution(char a, char b){
    if (a==b)return 0;
    if(lettres_concordantes(a,b))return C_SUB_CONCORDANT;
    return C_SUB_NON_CONCORDANT;
}



int min3(int a, int b, int c){
    return min(min(a,b),c);
}



int dist_naif_rec(char* x,char* y,int i, int j, int c, int dist){
    int lenX = strlen(x),lenY = strlen(y);
    if (( i == lenX ) && ( j == lenY)){
        if ((c <dist) || (dist == INF)){
            dist = c;
        }
    }
    else{
        if ((i<lenX) && (j<lenY))  dist = dist_naif_rec (x, y, i+1, j+1, c + cout_substitution(x[i],y[j]),dist);
        if (i <lenX)   dist = dist_naif_rec(x,y,i+1,j,c+ C_DEL, dist);
        if(j <lenY)    dist = dist_naif_rec(x, y, i, j+1, c + C_INS, dist);
    }
    return dist;
}


int dist_naif(char* x,char* y){     // return the distance of (x,y)
    return dist_naif_rec(x,y,0,0,0,INF);
}



int dist_1(char* x, char* y, int ** DP){
/*Function that calculates the distance between x and y of size n and m using an array of size n x m */   
    int INS,DEL,SUB;
    int n=strlen(x) ;
    int m=strlen(y);
    
    DP[0][0] = 0;
    for(int i=1;i<=n;i++){
        DP[i][0] = DP[i-1][0] + C_DEL;
    }

    for(int j=1;j<=m;j++){
        DP[0][j] = DP[0][j-1] + C_INS;
    }

    for( int i = 1 ; i <= n ; i ++){
        for (int j = 1 ; j <= m ; j++){
            
            INS = DP[i][j-1] + C_INS;
            DEL = DP[i-1][j] + C_DEL;
            SUB = DP[i-1][j-1] + cout_substitution(x[i-1] , y[j-1]);     
    
            DP[i][j] = min3(INS , DEL , SUB);
        }
    }
    
    return DP[n][m] ;
    
}


Align* sol_1(char* x, char* y, int** D){
    int n=strlen(x) ;
    int m=strlen(y);
    int i = n; 
    int j = m;
    
   
    Align* res = creer_alignement(n, m);
    res->iter=n+m-1;
    res->dist = D[n][m];
    
    
    while ((i > 0) && (j > 0)) {
        if ( (D[i][j] == D[i] [j-1] + C_INS)){
            res->x[res->iter] = '-';
            res->y[res->iter] = y[j-1];
            res->iter --;                
            j--;
        }
        else if ( (D[i][j] == D[i -1] [j] + C_DEL)) {
            res->x[res->iter] = x[i-1];
            res->y[res->iter] = '-';            
            res->iter --;                
            i--;
        }
        else if ( (D[i][j] == D[i -1][j -1] + cout_substitution(x[i-1] , y[j-1]))){           
            res->x[res->iter] = x[i-1];
            res->y[res->iter] = y[j-1];            
            res->iter --;
            i--;
            j--;
        }
        else{
            return NULL;        
        }
    }
    while (i > 0) {
        res->x[res->iter] = x[i-1];
        res->y[res->iter] = '-';
        res->iter --;                
        i--;
    }
    while (j > 0) {
        res->x[res->iter] = '-';
        res->y[res->iter] = y[j-1];
        res->iter --;                
        j--;
    }
    deletechar(res->x,'|');
    deletechar(res->y,'|');
    return res;
}






//print matrix (for testing)
void pM(int **D,int n,int m){
    printf("Dist Matrix\n");
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            printf("%d ",D[i][j]);
        }
        printf("\n");
    }
}





Align* PROG_DYN(duo_chaine* duo){
    
    if(duo==NULL){
        printf("Duo est = NULL");
        return NULL;
    }
    size_t n=strlen(duo->x);
    size_t m=strlen(duo->y);

    int** Dist = (int **) malloc((n+1 )* sizeof(int*));

    for(int i = 0; i <=n ; i ++){
        Dist[i] = (int*) malloc((m +1)* sizeof(int));
    }
    

    dist_1(duo->x,duo->y,Dist);
    
    Align* res = sol_1(duo->x,duo->y,Dist);

    int coup=calcul_cout(res);
    assert(coup==Dist[n][m]); // to make sure our solution is the optimale allignment

    printf("coût de calcul de l'alignement obtenu = %d  \nDistance d'édition optimale           = %d\n",coup,Dist[n][m]);
    for(int i = 0; i <= n ; i++){   free(Dist[i]);}
    
    free(Dist);

    return res;
}


void swap(int *i1,int *i2){
    int tmp=*i1;
    *i1=*i2;
    *i2=tmp;
    
}


int Dist_2(char* x,char* y,int n,int m, int** DP){

    n = strlen(x);
    m = strlen(y);
    int INS,DEL,SUB,iter1=1,iter0=0;
   
    for(int j=1;j<=m;j++){
        DP[0][j] = j* C_INS;
    }

    for(int i=1;i<=n;i++){
        DP[iter1][0] = DP[iter0][0] + C_DEL;
        for(int j=1;j<=m;j++){
            INS = DP[iter1][j-1] + C_INS;
            DEL = DP[iter0][j] + C_DEL;
            SUB = DP[iter0][j-1] + cout_substitution(x[i-1] , y[j-1]);     

            DP[iter1][j] = min3(INS , DEL , SUB);
        }
        swap(&iter0,&iter1);
    }
    return DP[iter0][m];

}



char* mot_gaps(int k){
    char * res = (char*) malloc( (k +1) * sizeof(char));
    res[k]='\0';
    for(int i = 0 ; i < k ; i++) res[i] = '-';
    
    return res;
}


Align* align_lettre_mot(char x, char* y, int m){
    int i=0;
    int cout_i=1e8;
    int cout_curr;
    Align* res = (Align*) malloc(sizeof(Align));
    for (int t=0;t<m;t++){
        cout_curr=cout_substitution(x,y[t]);
        if(cout_curr<cout_i){
            i=t;
            cout_i=cout_substitution(x,y[i]);
        }
        if(cout_curr==0){
            i=t;
            cout_i=cout_substitution(x,y[i]);
            break;
        }
    }
    if(cout_i<C_DEL+C_INS){
        res->x=mot_gaps(m);
        res->x[i]=x;
        res->y=strdup(y);
        res->size=m;
        return res;

    }else{
        res->x=mot_gaps(m+1);
        res->x[0]=x;
        res->y=(char*) malloc( (m+2) *sizeof(char));
        res->y[m+1]='\0';
        res->y[0]='-';
        res->size=m+1;
        for(int a=0;a<m;a++){
            res->y[a+1]=y[a];
        }
    }
    return res;
    
}



Align* concatener_alignements(Align*algn_1, Align* algn_2){

    algn_1->size = algn_1->size + algn_2->size;
    algn_1->x = (char *) realloc(algn_1->x,algn_1->size +1);
    algn_1->y = (char *) realloc(algn_1->y, algn_1->size +1); // realloue pour modifier la taille
    algn_1->y[algn_1->size]='\0';
    strcat(algn_1->x,algn_2->x);
    strcat(algn_1->y,algn_2->y);

    supprimer_alignement(algn_2);

    return algn_1;
}



int coupure(char * x, char* y, int n,int m,int** DP, int ** I){
    
    int INS,DEL,SUB;
    int iE = n/2;  //i étoile
    int iter0=0;
    int iter1=1;
   
    for(int j=1;j<=m;j++) {
        I[0][j]=j;
        DP[0][j] = DP[0][j-1] + C_INS;
    }

    for(int i=1;i<=n;i++){
        DP[iter1][0] = DP[iter0][0] + C_DEL;
        I[iter1][0] = 0;
        if (i==iE+1){
            for(int j=0;j<=m;j++) I[iter0][j]=j;
        }
        for(int j=1;j<=m;j++){
            INS = DP[iter1][j-1] + C_INS;
            DEL = DP[iter0][j] + C_DEL;
            SUB = DP[iter0][j-1] + cout_substitution(x[i-1] , y[j-1]);
            DP[iter1][j] = min3(INS , DEL , SUB);

            if(DP[iter1][j]==SUB)I[iter1][j]=I[iter0][j-1];
            if(DP[iter1][j]==DEL)I[iter1][j]=I[iter0][j];
            if(DP[iter1][j]==INS)I[iter1][j]=I[iter1][j-1];     

            
        }
        swap(&iter0,&iter1);
    }
    
    return I[iter0][m];
}





    

int test_coup(duo_chaine* duo){
    printf("test coupure\n");
    if(duo==NULL){
        printf("Duo est = NULL");
        return 0;
    }
    size_t n=strlen(duo->x);
    size_t m=strlen(duo->y);

    int** Dist = (int **) malloc((n+1 )* sizeof(int*));
    int** I = (int **) malloc((n+1 )* sizeof(int*));
    for(int i = 0; i <=n ; i ++){
        Dist[i] = (int*) malloc((m +1)* sizeof(int));
        I[i] = (int*) malloc((m +1)* sizeof(int));
    }
    

    dist_1(duo->x,duo->y,Dist);
    
    
    Align* res = sol_1(duo->x,duo->y,Dist);
    assert(calcul_cout(res)==res->dist);
    int dist2 = Dist_2(duo->x,duo->y,strlen(duo->x),strlen(duo->y), Dist);
    printf("dist par dist1 = %d  , par dist2 = %d \n",res->dist,dist2);
    afficher_alignement(res);

    int c = coupure(duo->x,duo->y,n,m,Dist,I);

    for(int i = 0; i <= n ; i++){   
        free(Dist[i]);
        free(I[i]);}
    
    free(Dist);
    free(I);

    return c;
}




Align * SOL_2(char * x, char* y,int n,int m, int** Dist, int** I){
    
    
    if (n == 0){
        Align* algn_res = (Align*) malloc(sizeof(Align));
        algn_res->x = mot_gaps(m);
        algn_res->y = strdup(y);
        algn_res->size = m;
        return  algn_res;
    }
    if (m == 0){
        Align* algn_res = (Align*) malloc(sizeof(Align));
        algn_res->x = strdup(x);
        algn_res->y = mot_gaps(n);
        algn_res->size = n;
        return  algn_res;
    }
    if(n==1){        
        Align* res=align_lettre_mot(x[0],y,m);
        assert(res!=NULL);
        return res;
    }
   
    Align* algn_res;
    int j = coupure(x,y,n,m,Dist,I);
    int i = n/2;


    char* xx=(char*)malloc((i+1)*sizeof(char)); //to get x[0..i[
    char* yy=(char*)malloc((j+1)*sizeof(char)); //to get y[0..i[
    strncpy(xx,x,i);
    xx[i]='\0';
    strncpy(yy,y,j);
    yy[j]='\0';
    
    Align* algn_1 = SOL_2(xx,yy,i,j,Dist,I);
    free(xx);
    free(yy);
    Align* algn_2 = SOL_2(x+i,y+j,n-i,m-j,Dist,I);
    
    algn_res = concatener_alignements(algn_1,algn_2);
    return algn_res;
}


Align* PROG_DYN_SOL2(duo_chaine* duo){
    
    if(duo==NULL){
        printf("Duo est = NULL");
        return NULL;
    }
    int n=strlen(duo->x);
    int m=strlen(duo->y);

    int** Dist = (int **) malloc((2 )* sizeof(int*));
    Dist[0] = (int*) malloc((m +1)* sizeof(int));
    Dist[1] = (int*) malloc((m +1)* sizeof(int));

    int** I = (int **) malloc((2 )* sizeof(int*));
    I[0] = (int*) malloc((m +1)* sizeof(int));
    I[1] = (int*) malloc((m +1)* sizeof(int));

    for(int t=0;t<=m;t++){
        Dist[0][t]=0;
        Dist[1][t]=0;
        I[0][t]=0;
        I[1][t]=0;
    }
    
    int dist2=Dist_2(duo->x,duo->y,n,m,Dist);
    Align* res = SOL_2(duo->x,duo->y,n,m,Dist,I);

    res->dist=dist2;
    int coup=calcul_cout(res);
    assert(coup==dist2); // to make sure our allignment is the optimale 
    printf("coup de calcule des l'alignement obtenu = %d  \nDistence d'édition optimal              = %d\n",coup,dist2);


    free(Dist[0]);
    free(Dist[1]);
    free(Dist);

    free(I[0]);
    free(I[1]);
    free(I);


    return res;
}

int calcul_cout(Align* res){
    int cout=0;
    for(int i =0;i<(int)strlen(res->x);i++){
        if(res->x[i]==res->y[i]){
            continue;}
        if(res->x[i]=='-'){            
            cout+=C_INS;
            continue;}
        if(res->y[i]=='-'){
            cout+=C_DEL;
            continue;}
        cout +=(cout_substitution(res->x[i],res->y[i]));
    }
    return cout;
}