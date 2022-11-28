#include <dirent.h>
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct_command.h"

void parcours(char* directory,struct_command* c){
    struct dirent *dir;
    DIR *d;
    d = opendir(directory);
    if (d!=NULL){
        while ((dir = readdir(d))!=NULL){   
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 && dir->d_name[0]!='.'){
                char retour[10000] = "";
                strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                if (compare(dir,c))
                {
                    printf("%s\n",retour);
                }  
                parcours(retour,c);
                
            }
        }
    }
    closedir(d);
}

void parcoursSimple(char* directory, int count){
    struct dirent *dir;
    DIR *d;
    d = opendir(directory);
    if (d!=NULL){
        while ((dir = readdir(d))!=NULL){   
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 && dir->d_name[0]!='.'){
                if (count==0)
                {
                    printf("%s\n",directory);
                    count++;
                }
                char retour[10000] = "";
                strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                printf("%s\n",retour);
                parcoursSimple(retour,count);
                
            }
        }
    }
    closedir(d);
}


int compare(struct dirent *dir, struct_command* c){
    if (c->name!=NULL && strcmp(dir->d_name,c->name)==0)
    {
        return 1;
        
    }
    return 0;
}

