#ifndef io_H
#define io_H

#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include"DATA_struct.h"
#include<dirent.h>




//a structure of a (liste chainé) of files with len as the max(strlen(x),strlen(y)) 
typedef struct _txtFile{
    char* Fname;
    int len;
    struct _txtFile* next;
}txtFile;

//read the genom file
duo_chaine* lire_genome(char* file_name);


//read the len max(x,y) of of a file 
int read_len_max(char* name_f);

// add the file f to the (Liste chainé) l in the right position (sorted list)
void  add_LF( txtFile** l,txtFile *f);

//reads all file names in the Directory Dit_name (maximum mx files) and returns it as a (List chainé) of type txtFile
txtFile* read_all_Fnam(const char* Dir_name,int mx);

//free the memory allocated by reading all the files names in Instances_genome
void delete_List_Files(txtFile* L);

//mesure memory 
long double  get_memory_usage() ;

#endif