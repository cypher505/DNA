#include"../src/math.h"
#include"../src/DATA_struct.h"
#include"../src/io.h"


// a script to compare DIST_1 and DIST_2

int main(){
    clock_t start,end;
    double tmp_de_calcul = 0;
    duo_chaine* duo;
    char buff[256];
    int cmp=0;
    txtFile * ALLFILES = read_all_Fnam("../Instances_genome",50);
    txtFile * Files=ALLFILES;
    FILE* data_file1 = fopen("../DATA/Temps_DIST1_ALL_INST.txt","w");
    FILE* data_file2 = fopen("../DATA/Temps_DIST2_ALL_INST.txt","w");
    
    while ( Files && (tmp_de_calcul < 200 ) && cmp<45) {
        printf("\n______________________________________________\n\n");
        cmp++;
        sprintf(buff,"../Instances_genome/%s",Files->Fname);
        printf("pour %s \n",buff);
        duo = lire_genome(buff);
        
        int** Dist = (int **) malloc((duo->n+1 )* sizeof(int*));
        for(int i = 0; i <=duo->n ; i ++){
            Dist[i] = (int*) malloc((duo->m +1)* sizeof(int));
        }
        

        printf("DIST1:\n");
        start = clock();
        dist_1(duo->x,duo->y,Dist);
        end = clock();
        
        tmp_de_calcul = (end - start) / CLOCKS_PER_SEC;
        fprintf(data_file1,"%d %.4f\n",Files->len,tmp_de_calcul);

        for(int i = 0; i <= duo->n ; i++){   free(Dist[i]);}
        free(Dist);
        //////////////////////////////////////////
        Dist = (int **) malloc((2 )* sizeof(int*));
        Dist[0] = (int*) malloc((duo->m +1)* sizeof(int));
        Dist[1] = (int*) malloc((duo->m +1)* sizeof(int));

        

        printf("DIST2:\n");
        start = clock();
        Dist_2(duo->x,duo->y,duo->n,duo->m, Dist);
        end = clock();
        
        tmp_de_calcul = (end - start) / CLOCKS_PER_SEC;
        fprintf(data_file2,"%d %.4f\n",Files->len,tmp_de_calcul);

        free(Dist[0]);
        free(Dist[1]);
        free(Dist);

        
        Files=Files->next;
        
        
        supprimer_duo_chaine(duo);
        
    }
    fclose(data_file1);
    fclose(data_file2);
    delete_List_Files(ALLFILES);
    return 0;
}
