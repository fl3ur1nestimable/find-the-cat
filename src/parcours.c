#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parcours(char* directory){
    struct dirent *dir;
    DIR *d;
    d = opendir(directory);
    if (d!=NULL){
        while ((dir = readdir(d))!=NULL){   
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 && dir->d_name[0]!='.'){
                char retour[10000] = "";
                strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                printf("%s\n",retour);          
                parcours(retour);
            }
        }
    }
    closedir(d);
}

void parcours_name(char* directory, char* name){
    struct dirent *dir;
    DIR *d;
    d = opendir(directory);
    if (d!=NULL && name!=NULL){
        while ((dir = readdir(d))!=NULL){   
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 && dir->d_name[0]!='.'){
                char retour[10000] = "";
                strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                if (strcmp(dir->d_name,name)==0){
                    printf("%s\n",retour);
                }
                parcours_name(retour,name);
            }
        }
    }
    closedir(d);
}
