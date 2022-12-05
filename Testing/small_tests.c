#include"../src/math.h"
#include"../src/DATA_struct.h"
#include"../src/io.h"

int main(){ 

    clock_t temp_init,temp_fin;
    int** Dist;
    
    
    double temp = 0.0;
    int dist,buff;
    char string[256];
    char bf[256]="Instances_genome/";

    printf("1 :Test the reading functions\n");
    printf("2 :Test dist_naif_rec\n"); 
    printf("3 :Calculer le temps utilisé pour dist_naif \n");
    printf("4 :Calculer la distance d'un Inst par Dist1 :\n");
    printf("5 :Calculer la distance d'un Inst par Dist2 :\n");
    printf("6 :Test SOL_1 :\n");
    printf("7 :Test SOL_2 :\n");
    printf("8 :Tester le BONSU Q30\n");
    scanf("%d",&buff);
    duo_chaine* duo;
    Align* res;

    switch (buff){
    
    case 1:/*Testing our reading functions*/
        printf("______________________________________\n\n");
        printf("Testing the reading functions with the instance Inst_0000010_7\n");
        duo_chaine* test = lire_genome("Instances_genome/Inst_0000010_7.adn");
        afficher_duo_chaine(test);
        supprimer_duo_chaine(test);
        break;

    case 2://Testing of our naive method
        printf("______________________________________\n\n");
        printf("\nTest de la méthode naïve de calc dist d'édition \n");

        duo_chaine* inst_10_8 = lire_genome("Instances_genome/Inst_0000010_8.adn");
        dist = dist_naif(inst_10_8->x,inst_10_8->y);
        printf("Distance d'édition pour 10_8: %d\nRésultat correct :%d\n",dist,(dist==2));
        supprimer_duo_chaine(inst_10_8);

        duo_chaine* inst_10_7 = lire_genome("Instances_genome/Inst_0000010_7.adn");
        dist = dist_naif(inst_10_7->x,inst_10_7->y);
        printf("Distance d'édition pour 10_7: %d\nRésultat correct :%d\n",dist,(dist==8));
        supprimer_duo_chaine(inst_10_7);

        duo_chaine* Inst_10_44 = lire_genome("Instances_genome/Inst_0000010_44.adn");
        dist = dist_naif(Inst_10_44->x,Inst_10_44->y);
        printf("Distance d'édition pour 10_44: %d\nRésultat correct :%d\n",dist,(dist==10));
        supprimer_duo_chaine(Inst_10_44);
        break;

    case 3:
        printf("______________________________________\n\n");
        printf("Enter the Instance you want to test example (Inst_0000013_89.adn)\n");
        scanf("%s",string);
        
        strcat(bf,string);
        
        duo = lire_genome(bf);

        temp_init = clock();
        dist = dist_naif(duo->x,duo->y);
        temp_fin = clock();
    
        temp = (temp_fin - temp_init) / CLOCKS_PER_SEC;
        printf("Temps de calcul pour  Inst_0000013_89: %.2f  Distance d'édition : %d\n", temp,dist);
        supprimer_duo_chaine(duo);

        break;
    case 4:
        printf("______________________________________\n\n");
        printf("Enter the Instance you want to test example (Inst_0000013_89.adn)\n");
        scanf("%s",string);
        strcat(bf,string);
        duo = lire_genome(bf);
        Dist = (int **) malloc((duo->n+1 )* sizeof(int*));
        for(int i = 0; i <=duo->n ; i ++){
            Dist[i] = (int*) malloc((duo->m +1)* sizeof(int));
        }
        printf("la Distance d'édition par Dist1 =%d\n",dist_1(duo->x,duo->y,Dist));
        for(int i = 0; i <= duo->n ; i++){free(Dist[i]);}
        free(Dist);
        supprimer_duo_chaine(duo);
    
        break;
    case 5:
        printf("______________________________________\n\n");
        printf("Enter the Instance you want to test example (Inst_0000013_89.adn)\n");
        scanf("%s",string);
        strcat(bf,string);
        duo = lire_genome(bf);
        Dist = (int **) malloc((2 )* sizeof(int*));
        Dist[0] = (int*) malloc((duo->m +1)* sizeof(int));
        Dist[1] = (int*) malloc((duo->m +1)* sizeof(int));
        printf("la Distance d'édition par Dist1 =%d\n",Dist_2(duo->x,duo->y,duo->n,duo->m,Dist));
        free(Dist[0]);
        free(Dist[1]);
        free(Dist);
        supprimer_duo_chaine(duo);
        break;
    case 6:
        printf("______________________________________\n\n");
        printf("Enter the Instance you want to test example (Inst_0000013_89.adn)\n");
        scanf("%s",string);
        
        
        strcat(bf,string);
        
        duo = lire_genome(bf);

        temp_init = clock();
        res= PROG_DYN(duo);
        temp_fin = clock();
        temp = (temp_fin - temp_init) / CLOCKS_PER_SEC;
        printf("\n");
        afficher_alignement(res);
        printf("\n");
        check_sanity(res,duo);
        printf("\nTemps de calcul PROG_DYN() pour  %s: %.2f \n",string,temp);
        printf("SOL_1 valide\n");
        supprimer_duo_chaine(duo);
        supprimer_alignement(res);        
        break;
    case 7:
        printf("______________________________________\n\n");
        printf("Enter the Instance you want to test example (Inst_0000013_89.adn)\n");
        scanf("%s",string);
        strcat(bf,string);
        duo = lire_genome(bf);
        temp_init = clock();
        res= PROG_DYN_SOL2(duo);
        temp_fin = clock();
        temp = (temp_fin - temp_init) / CLOCKS_PER_SEC;
        printf("\n");
        afficher_alignement(res);
        printf("\n");
        check_sanity(res,duo);
        printf("\nTemps de calcul PROG_DYN_2() pour  %s: %.2f \n",string,temp);
        printf("SOL_2 valide\n");
        supprimer_alignement(res);
        supprimer_duo_chaine(duo);
        break;
    case 8:
        printf("______________________________________\n\n");
        printf("pour L'INST_BONUS.adn dans le fichier Testing : \n");
        duo = lire_genome("Instances_genome/Inst_0000125_BO.adn");
        printf("Pour l'instance Inst_0000125_BO\n");
        res= PROG_DYN_SOL2(duo);
        int coup_algn=calcul_cout(res);
        printf("Le cout de l'Alignement BONUS = %d\n",coup_algn);
        int BONUS=(duo->n - duo->m)*C_DEL;
        printf("|x|*|y|*D_DEL = %d\n",BONUS);
        supprimer_duo_chaine(duo);
        supprimer_alignement(res);
        assert(BONUS==coup_algn);
        printf("______________________________________\n\n");

        printf("pour L'INST_BONUS.adn dans le fichier Testing : \n");
        duo = lire_genome("Instances_genome/Inst_0000200_BO.adn");
        printf("Pour l'instance Inst_0000200_BO\n");
        res= PROG_DYN_SOL2(duo);
        coup_algn=calcul_cout(res);
        printf("Le cout de l'Alignement BONUS = %d\n",coup_algn);
        BONUS=(duo->n - duo->m)*C_DEL;
        printf("|x|*|y|*D_DEL = %d\n",BONUS);
        supprimer_duo_chaine(duo);
        supprimer_alignement(res);
        assert(BONUS==coup_algn);
        printf("______________________________________\n\n");

        printf("pour L'INST_BONUS.adn dans le fichier Testing : \n");
        duo = lire_genome("Instances_genome/Inst_0000250_BO.adn");
        printf("Pour l'instance Inst_0000250_BO\n");
        res= PROG_DYN_SOL2(duo);
        coup_algn=calcul_cout(res);
        printf("Le cout de l'Alignement BONUS = %d\n",coup_algn);
        BONUS=(duo->n - duo->m)*C_DEL;
        supprimer_alignement(res);
        printf("|x|*|y|*D_DEL = %d\n",BONUS);
        assert(BONUS==coup_algn);
        printf("______________________________________\n\n");
        supprimer_duo_chaine(duo);

        break;
                
    default:
        break;
    }
    return 0;    
}