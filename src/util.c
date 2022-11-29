#include <dirent.h>
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct_command.h"
#include <sys/stat.h>

void parcours(char* directory,struct_command* c){
    struct dirent *dir;
    DIR *d;
    d = opendir(directory);
    if (d!=NULL){
        while ((dir = readdir(d))!=NULL){ 
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 && dir->d_name[0]!='.'){
                char retour[10000] = "";
                strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                //printf("%s\n",c->size);
                if (compare_name(dir,c) && compare_size(retour,c))
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


int compare_name(struct dirent *dir, struct_command* c){
    if ((c->name!=NULL && strcmp(dir->d_name,c->name)==0) || c->name==NULL)
    {
        return 1;
        
    }
    return 0;
}


int compare_size(char* chemin_fichier, struct_command* c){
    struct stat fichier;
    int plusmoins=0;
    int unite=0;
    if (c->size ==NULL){
        return 1;
    }

    
    else {
        int taillechaine=strlen(c->size);
        int taillefichier;
        char* newchaine=malloc(strlen(c->size)*sizeof(char));
        strcpy(newchaine,c->size);  
        if (c->size[taillechaine-1]=='c' || c->size[taillechaine-1]=='k' || c->size[taillechaine-1]=='G' || c->size[taillechaine-1]=='M'){
            unite++;
        }
        if (c->size[0]=='+' || c->size[0]=='-'){
            plusmoins++;
        }
        if (unite>0 && plusmoins>0){
            newchaine++;
            newchaine[strlen(newchaine)-1]='\0';
            taillefichier=atoi(newchaine);          
        }
        else if (unite>0 && plusmoins==0){
            newchaine[strlen(newchaine)-1]='\0';
            taillefichier=atoi(newchaine);
        }
        else if(unite==0 && plusmoins==0){
            taillefichier=atoi(newchaine);
        }
        else if(unite==0 && plusmoins>0){
            newchaine++;
            taillefichier=atoi(newchaine); 
        }
        
        stat(chemin_fichier, &fichier);

        if (unite>0){
            if (c->size[taillechaine-1]=='k'){
                taillefichier=taillefichier*1024;
            }
        }
        else if (unite>0){
            if (c->size[taillechaine-1]=='M'){
                taillefichier=taillefichier*1024*1024;
            }
        }
        else if (unite>0){
            if (c->size[taillechaine-1]=='G'){
                taillefichier=taillefichier*1024*1024*1024;
            }
        }
        if (plusmoins>0 && c->size[0]=='+'){
            if (fichier.st_size>taillefichier){
                return 1;
            }
        }
        else if (plusmoins>0 && c->size[0]=='-'){
            if (fichier.st_size<taillefichier){
                return 1;
            }
        }
        else if (plusmoins==0){
            if (fichier.st_size==taillefichier){
                return 1;
            }
        }
        else {return 0;}
    return 0;
    }
}

