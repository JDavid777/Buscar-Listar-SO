#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>


void searchList(char* path,char* pattern);
void help();
int main (int argc, char* argv[]){

    if (strcmp(argv[1],"--h")==0)
    {
        help();
    }
    
    char path[NAME_MAX];
    if (argc==1)
    {
        printf("Especifique un patron de busqueda. ver ayuda.");
    }
    
    else if(argc==2){
        strcpy(path,".");
        searchList(path,argv[1]);
        exit(EXIT_SUCCESS);
    }
    for (int i=1; i<argc;i++){
        searchList(argv[i],argv[i+1]);
        i++;// aumentamos nuemamente para que no haga todas las iteraciones y no se desborde el vector argv.
    }

}
/**
 * @param Ruta a listar
 * @param Patron de busqueda para buscar y listar
*/
void searchList (char* path,char* pattern){
    
    DIR* d;
    struct dirent* ent;
    struct stat buf;
    char* path2;
    d= opendir(path);
    
    while ((ent = readdir(d)) != NULL){

        if(ent->d_name[0] != '.'){
           
            path2=(char*)malloc(strlen(path)+strlen(ent->d_name) + 2);
            strcpy(path2,path);
            strcat(path2,"/");
            strcat(path2,ent->d_name);
            stat(path2,&buf);
            mode_t mode=buf.st_mode;
             if(strstr(ent->d_name,pattern)!=NULL){
                printf("\033[32m%s\n", path2);
            }
            if (S_ISDIR(mode)){
                searchList(path2,pattern);
            }   
        }
    }
    closedir(d);
}  
void help(){
    printf("\n*******Sintaxis para ./find.*******\n");
    printf("\033[31m ./find "" \033[34m [ruta(opcional)]""\033[34m [arg]\n");
    printf("  arg ""\033[31mPatron de busqueda.\n");
    exit(EXIT_SUCCESS);
}