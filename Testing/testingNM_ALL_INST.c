#include"../src/math.h"
#include"../src/DATA_struct.h"
#include"../src/io.h"


int main(){
    
    clock_t start,end;
    double tmp_de_calcul = 0;
    duo_chaine* duo;
    int dist;
    char buff[256];
    txtFile * Files = read_all_Fnam("../Instances_genome",50);
    FILE* data_file1 = fopen("../DATA/Temps_NM.txt","w");
    FILE* data_file2 = fopen("../DATA/mem_NM.txt","w");
    long double baseMEM=get_memory_usage(),ld2;
    while ( Files && (tmp_de_calcul < 60)) {
        
        sprintf(buff,"../Instances_genome/%s",Files->Fname);
        Files=Files->next;
        printf("___________________________\n\npour %s \n",buff);
        duo = lire_genome(buff);

        start = clock();
        dist = dist_naif(duo->x,duo->y);
        end = clock();
        tmp_de_calcul = (end - start) / CLOCKS_PER_SEC;
        printf("pour l'Instance : %s dist = %d temps de calcul =%f\n",Files->Fname,dist,tmp_de_calcul);
        fprintf(data_file1,"%d %.4f\n",Files->len,tmp_de_calcul);
       
        
        ld2 =get_memory_usage()-baseMEM;
         printf("memory =%Lf\n",ld2);
        
        fprintf(data_file2,"%d %.4Lf \n",Files->len,ld2);


        supprimer_duo_chaine(duo);
        
    }
    return 0;
    
}