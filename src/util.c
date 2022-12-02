#include <dirent.h>
#include "util.h"
#include <stdio.h>                                                    
#include <string.h>
#include <stdlib.h>
#include "struct_command.h"
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>

void parcours(char* directory,struct_command* c){
    struct dirent *dir;
    DIR *d;
    d = opendir(directory);
    if (d!=NULL){
        while ((dir = readdir(d))!=NULL){ 
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 && dir->d_name[0]!='.'){
                char retour[10000] = "";
                strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                //printf("%s\n",c->                          size);
                if (compare_name(dir,c) && compare_size(retour,c) && compare_date(retour,c))
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

        if (c->size[0]=='+'){
            plusmoins++;
        }
        if (unite>0 && plusmoins>0){
            newchaine++;
            newchaine[strlen(newchaine)-1]='\0';         
        }
        else if (unite>0 && plusmoins==0){
            newchaine[strlen(newchaine)-1]='\0';
        }
        else if(unite==0 && plusmoins==0){
        }
        else if(unite==0 && plusmoins>0){
            newchaine++;
        }
        for (int i=0;i<strlen(newchaine);i++){
            if (!isdigit(newchaine[i])){
                printf("Format : (+/-)taille(c/k/M/G)\n");
                exit(EXIT_FAILURE);
            }
        }
        taillefichier=atoi(newchaine);
        stat(chemin_fichier, &fichier);
        unsigned long vraitaille = (unsigned long) taillefichier;
        if (unite>0){
            if (c->size[taillechaine-1]=='k'){
                vraitaille=vraitaille*1024;
            }
        
            if (c->size[taillechaine-1]=='M'){
                vraitaille=vraitaille*1024*1024;
            }
            if (c->size[taillechaine-1]=='G'){
                vraitaille=vraitaille*1024*1024*1024;
            }
        }
        if (plusmoins>0 && c->size[0]=='+'){
            if (fichier.st_size>vraitaille){
                return 1;
            }
        }
        else if (plusmoins>0 && c->size[0]=='-'){
            if (fichier.st_size<vraitaille){
                return 1;
            }
        }
        else if (plusmoins==0){
            if (fichier.st_size==vraitaille){
                return 1;
            }
        }
        else {return 0;}
    return 0;
    }
}


int compare_date(char* chemin_fichier, struct_command* c){
    struct stat fichier;
    int plusmoins=0;
    if (c->date ==NULL){
        return 1;
    }
    else {
        int taillechaine=strlen(c->date);
        char* newchaine1=malloc(strlen(c->date)*sizeof(char));
        strcpy(newchaine1,c->date);  
        if (!(c->date[taillechaine-1]=='m' || c->date[taillechaine-1]=='h' || c->date[taillechaine-1]=='j')){
            printf("il faut une unité : m(minutes) h(heures) j(jours)\n");
            exit(EXIT_FAILURE);
        }
        if (c->date[0]=='+'){
            plusmoins++;
        }
        if (plusmoins>0){
            newchaine1++;
            newchaine1[strlen(newchaine1)-1]='\0';         
        }
        else if (plusmoins==0){
            newchaine1[strlen(newchaine1)-1]='\0';
        }

        for (int i=0;i<strlen(newchaine1);i++){
            if (!isdigit(newchaine1[i])){
                printf("Format : (+)durée(m/h/j)\n");
                exit(EXIT_FAILURE);
            }
        }
        int timeasked=atoi(newchaine1);
        double truetime= (double) timeasked;
        
        time_t ajd = time(NULL);
        stat(chemin_fichier, &fichier);
        time_t dateacces = fichier.st_atime;
        double diff = difftime(ajd,dateacces);
        
        if (c->date[taillechaine-1]=='m'){
            diff=diff/60;
        }
        else if (c->date[taillechaine-1]=='h'){
            diff=diff/60/60;
        }
        else if (c->date[taillechaine-1]=='j'){
            diff=diff/60/60/24;
        }

        if (plusmoins==0){
            if (diff<=truetime){
                return 1;
            }
        }

        else if (plusmoins>0){
            if (diff>truetime){
                return 1;
            }
        }

        return 0;         
    }
}