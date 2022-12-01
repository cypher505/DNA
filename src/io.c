#include"io.h"
#include"DATA_struct.h"

duo_chaine* lire_genome(char* file_name){
    FILE* F = fopen(file_name,"r");

    if(F == NULL){
        printf("Ereur de lecture\n");
        return NULL;
    }

    int n,m;
    char buffer[256];

    fgets(buffer,256,F);
    if(sscanf(buffer,"%d",&n)!=1){
        printf("Erreur de lecture : n\n");
        return NULL;
    }

    fgets(buffer,256,F);
    if(sscanf(buffer,"%d",&m)!=1){
        printf("Erreur de lecture : m\n");
        return NULL;
    }

    char bufferX[2*n +1];
    fgets(bufferX,2*n,F);

    
    
    while(fgetc(F)!='\n');

    
    char bufferY[2*m + 1];
    fgets(bufferY,2*m,F);
    char* x = (char*) malloc( (n+1) * sizeof(char));
    char* y = (char*) malloc ( (m+1) * sizeof(char));

    int i;
    int j = 0;
    for(i = 0 ; i < 2*n ; i = i + 2){
        x[j++] = bufferX[i];
    }

    j = 0;
    for(i = 0 ; i < 2*m ; i = i +2){
        y[j++] = bufferY[i];
    }
    x[n] = '\0';
    y[m] = '\0';

    duo_chaine* res = creer_duo_chaine(x,y,n,m);

    fclose(F);
    return res;
}



void add_LF( txtFile** l,txtFile *f){
    txtFile* tmp=*l;
    printf("added %s\n",f->Fname);
    if (*l==NULL){
        *l=f;
        f->next=NULL;
    }else {
        if(tmp->len > f->len ){
            f->next=tmp;
            *l=f;
            return;
        }
        while (tmp->next!=NULL &&(tmp->next->len < f->len)){
            tmp=tmp->next;
        }
        if(tmp->next==NULL){
            tmp->next=f;
            f->next=NULL;
        }else{
            
            txtFile* ff=tmp->next;
            tmp->next=f;
            f->next=ff;
        }

    }
    
    
}


int read_len_max(char* name_f){
    char* tmp=strdup(name_f);
    char *ptr = strtok(tmp, "_");
    ptr = strtok(NULL, "_");
    int i=atoi(ptr);
    free(tmp);
    return i;
}


txtFile * read_all_Fnam(const char* Dir_name, int mx){

    txtFile* list_Fnames ;
    list_Fnames=NULL;
    DIR* rep = opendir(Dir_name);
    struct dirent * file = NULL;    
    if(rep == NULL){
        printf("error in opening the DIR\n");
        return NULL;
    }

    int i = 0;
    while ((i < mx) && ((file = readdir(rep)))){
        if ( ( strcmp(file->d_name,".") != 0 ) && (strcmp(file->d_name,"..") != 0) ){

            txtFile* f=(txtFile*) malloc(sizeof(txtFile));
            f->Fname=strdup(file->d_name);
            f->len=read_len_max(f->Fname);
            
            add_LF(&list_Fnames,f);
            i++;
        }
        
    }
    closedir(rep);
    
    return list_Fnames;  
}


void delete_List_Files(txtFile* L){
    if(L==NULL)return;
    txtFile* tmp;
    while(L){
        tmp=L->next;
        free(L->Fname);
        free(L);
        L=tmp;
    }
}



long double  get_memory_usage() {  
    struct rusage r_usage;
    int ret = getrusage(RUSAGE_SELF,&r_usage);
    if(ret != 0) printf("Error in getrusage. errno = %d\n", errno);
       // printf("Memory usage: %ld kilobytes\n",r_usage.ru_maxrss);
    
   return r_usage.ru_maxrss;
}