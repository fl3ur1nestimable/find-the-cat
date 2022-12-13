#include <dirent.h>
#include "util.h"
#include <stdio.h>                                                    
#include <string.h>
#include <stdlib.h>
#include "struct_command.h"
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>
#include <regex.h>
//#include "MegaMimes.h"


void parcours(char* directorypath,struct_command* c/*,int count*/){
    struct dirent *dir;
    DIR *d;
    //char* directory=malloc(strlen(directorypath)*sizeof(char)); 
    char directory[strlen(directorypath)];
    strcpy(directory,directorypath);
    if (directory[strlen(directorypath)-1]=='/')
    {
        directory[strlen(directory)-1]='\0';
    }
    d = opendir(directory);
    if (d!=NULL){
        while ((dir = readdir(d))!=NULL){ 
            if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 && dir->d_name[0]!='.'){
                /*if (count==0){
                    printf("%s\n",directory);
                    count++;
                }*/
                char retour[10000] = "";
                strcat(strcat(strcat(retour,directory),"/"),dir->d_name);
                if ((compare_name(dir,retour, c)||compare_regex(dir,retour,c)) && compare_size(retour,c) && compare_date(retour,c) && compare_dir(dir, retour,c) /*&& compare_mime(retour,c)*/)
                {
                    printf("%s\n",retour);
                }  
                parcours(retour,c/*,count*/);
            }
        }
    }
    closedir(d);
}

void parcoursSimple(char* directorypath, int count){
    struct dirent *dir;
    DIR *d;

    //char* directory=malloc(strlen(directorypath)*sizeof(char));
    char directory[strlen(directorypath)];
    strcpy(directory,directorypath);
    if (directory[strlen(directorypath)-1]=='/')
    {
        directory[strlen(directory)-1]='\0';
    }
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

int compare_name(struct dirent *dir,char* cheminfichier, struct_command* c){
    if (c->name==NULL){
        return 1;
    }
    else{
        if (isdir(cheminfichier)==1){
            return 0;
        }
        else{
            if (strcmp(dir->d_name,c->name)==0){
                return 1;
            }
        }
    }
    return 0;
}

int compare_regex(struct dirent *dir, char* cheminfichier, struct_command* c){
    if(c->name==NULL){
        return 1;
    }

    else{
        if (isdir(cheminfichier)==1){
            return 0;
        }
        else{
        int err;
        regex_t preg;
        const char *str_request = dir->d_name;
        const char *str_regex = c->name;    
        err = regcomp(&preg,str_regex,0);
        if (err == 0){
            int match;
            match = regexec(&preg, str_request,0,NULL,0);
            regfree(&preg);
            if (match==0)
            {
                return 1;   
            }
        }
        
    }
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

    if (isdir(chemin_fichier)==1){
            return 0;
        }
    else {
        int taillechaine=strlen(c->size);
        int taillefichier;
        char newchaine[strlen(c->size)];
        strcpy(newchaine,c->size);  
        if (c->size[taillechaine-1]=='c' || c->size[taillechaine-1]=='k' || c->size[taillechaine-1]=='G' || c->size[taillechaine-1]=='M'){
            unite++;
        }

        if (c->size[0]=='+'||c->size[0]=='-'){
            plusmoins++;
        }
        if (unite>0 && plusmoins>0){
            for (int i=0;i<(int)strlen(newchaine);i++){
                newchaine[i]=newchaine[i+1];
            }
            newchaine[strlen(newchaine)-1]='\0';         
        }
        else if (unite>0 && plusmoins==0){
            newchaine[strlen(newchaine)-1]='\0';
        }
        else if(unite==0 && plusmoins==0){
        }
        else if(unite==0 && plusmoins>0){
            for (int i=0;i<(int)strlen(newchaine);i++){
                newchaine[i]=newchaine[i+1];
            }
        }
        for (int i=0;i<(int)strlen(newchaine);i++){
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
            if ((long unsigned int)fichier.st_size>vraitaille){
                return 1;
            }
        }
        else if (plusmoins>0 && c->size[0]=='-'){
            if ((long unsigned int)fichier.st_size<vraitaille){
                return 1;
            }
        }
        else if (plusmoins==0){
            if ((long unsigned int)fichier.st_size==vraitaille){
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
    if (isdir(chemin_fichier)==1){
            return 0;
        }
    else {
        int taillechaine=strlen(c->date);
        char newchaine1[strlen(c->date)];
        //char* newchaine1=malloc(strlen(c->date)*sizeof(char));
        strcpy(newchaine1,c->date);  
        if (!(c->date[taillechaine-1]=='m' || c->date[taillechaine-1]=='h' || c->date[taillechaine-1]=='j')){
            printf("il faut une unité : m(minutes) h(heures) j(jours)\n");
            exit(EXIT_FAILURE);
        }
        if (c->date[0]=='+'){
            plusmoins++;
        }
        if (plusmoins>0){
            for (int i=0;i<(int)strlen(newchaine1);i++){
                newchaine1[i]=newchaine1[i+1];
            }
            newchaine1[strlen(newchaine1)-1]='\0';         
        }
        else if (plusmoins==0){
            newchaine1[strlen(newchaine1)-1]='\0';
        }

        for (int i=0;i<(int)strlen(newchaine1);i++){
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

/*int compare_mime(char* chemin_fichier, struct_command* c){
    //compare le mime type du fichier avec le mime type demandé

    if (c->mime==NULL){
        return 1;
    }
    else {    
        char* mime = getMegaMimeType(chemin_fichier);
        if (mime!=NULL){  
            char mime2[strlen(mime)];
            strcpy(mime2,mime);
            for (int i=0;i<(int)strlen(mime2);i++){
                if (mime2[i]=='/'){
                    mime2[i]='\0';
                    i=(int)strlen(mime2);
                }
            }      
            if (strcmp(mime,c->mime)==0){
                return 1;
            }
            else if (strcmp(mime2,c->mime)==0){
                return 1;
            }
            else {
                return 0;
            }
        }
    return 0;
    }
}*/

int compare_dir(struct dirent *dir, char* testfichier, struct_command* c){
    if (c->yesdir==NULL){
        return 1;
    }
    else if (c->yesdir==1 && c->dir!=NULL){
        char directory[strlen(c->dir)];
        strcpy(directory,c->dir);
        if (directory[strlen(directory)-1]=='/')
        {
            directory[strlen(directory)-1]='\0';
        }
        DIR *d;
        d = opendir(testfichier);
        if(d!=NULL){   
            closedir(d);
            if (strcmp(dir->d_name,directory)==0){
            return 1;
            }
            else {
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else if (c->yesdir==1){
        DIR *d;
        d = opendir(testfichier);
        if(d!=NULL){   
            closedir(d) ;
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

int isdir(char* chemin_fichier){
    struct stat fichier;
    stat(chemin_fichier, &fichier);
    if (S_ISDIR(fichier.st_mode)){
        return 1;
    }
    else {
        return 0;
    }
}
