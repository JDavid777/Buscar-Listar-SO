#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

void list_dir(char* dir);
int main (int argc, char* argv[]){
    char dir[NAME_MAX]; 
    if(argc==1){
        strcpy(dir,".");
        list_dir(dir);
        exit(EXIT_SUCCESS);
    }
    for (int i=1; i<argc;i++){
        list_dir(argv[i]);
   }
  // exit(EXIT_SUCCESS);
}
/**
 * @param Ruta a listar
*/
void list_dir (char* dir){
    DIR* d;
    struct dirent* ent;
    struct stat buf;
    char* dir2;
    d= opendir(dir);
    
    
    while ((ent = readdir(d)) != NULL){
        if(ent->d_name[0] != '.'){
            printf("\033[34m%s\n", ent-> d_name);
            dir2=(char*)malloc(strlen(dir)+strlen(ent->d_name) + 2);
            strcpy(dir2,dir);
            strcat(dir2,"/");
            strcat(dir2,ent->d_name);
            stat(dir2,&buf);
            mode_t mode=buf.st_mode;
        
            if (S_ISDIR(mode)){
                printf("\033[35m%s\n", ent-> d_name);
                list_dir(dir2);
            }
            
        }
    }
    closedir(d);
}  
