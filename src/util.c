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
                
                if (c->name!=NULL && compareName(dir,c->name))
                {
                    char retour[10000] = "";
                    strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                    printf("%s\n",retour);          
                    parcours(retour,c);
                }
                else if (c->name==NULL)
                {
                    char retour[10000] = "";
                    strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                    printf("%s\n",retour);          
                    parcours(retour,c);
                }
                
                else
                {
                    continue;
                }
                
            }
        }
    }
    closedir(d);
}


int compareName(struct dirent *dir, char* name){
    if (strcmp(dir->d_name,name)==0)
    {
        return 1;
    }
    return 0;
}
