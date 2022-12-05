#include"../src/math.h"
#include"../src/DATA_struct.h"
#include"../src/io.h"



int main(){
    clock_t start,end;
    double tmp_de_calcul = 0;
    duo_chaine* duo;

    char buff[256];
    Align *res;
    Align* res2 ;
    txtFile * ALLFILES = read_all_Fnam("../Instances_genome",50);
    txtFile * Files=ALLFILES;
    FILE* data_file1 = fopen("../DATA/Temps_DP_SOL1_ALL_INST.txt","w");
    FILE* data_file2 = fopen("../DATA/Temps_DP_SOL2_ALL_INST.txt","w");
    
    while ( Files && (tmp_de_calcul < 20 )) {
        printf("\n______________________________________________\n\n");

        sprintf(buff,"../Instances_genome/%s",Files->Fname);
        printf("pour %s \n",buff);
        duo = lire_genome(buff);

        printf("SOL_1:\n");
        start = clock();
        res = PROG_DYN(duo);
        end = clock();
        check_sanity(res,duo);
        tmp_de_calcul = (end - start) / CLOCKS_PER_SEC;
        fprintf(data_file1,"%d %.4f\n",Files->len,tmp_de_calcul);

        printf("\nSOL_2:\n");
        start = clock();
        res2 = PROG_DYN_SOL2(duo);
        end = clock();
        check_sanity(res2,duo);
        tmp_de_calcul = (end - start) / CLOCKS_PER_SEC;
        fprintf(data_file2,"%d %.4f\n",Files->len,tmp_de_calcul);
        
        Files=Files->next;
        
        
        supprimer_duo_chaine(duo);
        supprimer_alignement(res);
        supprimer_alignement(res2);
    }
    fclose(data_file1);
    fclose(data_file2);
    delete_List_Files(ALLFILES);
    return 0;
}
