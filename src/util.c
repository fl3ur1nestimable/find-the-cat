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
#include "MegaMimes.h"

void parcours(char* directorypath,struct_command* c,int count){
    char path[1000];
    struct dirent *dp;
    if (directorypath[strlen(directorypath)-1]=='/')
    {
        directorypath[strlen(directorypath)-1]='\0';
    }
    DIR *dir = opendir(directorypath);
    if(!dir){
        return;
    }
    while ((dp=readdir(dir))!=NULL)
    { 
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0  && dp->d_name[0]!='.')
        {
            if (count==0){
                if ((c->yesdir==1)&&(c->dir==NULL)){
                if (c->color != NULL && strcmp(c->color,"true")==0) printf("\033[1;33m");
                printf("%s\n",directorypath);
                count++;
                }   
            }
            strcpy(path, directorypath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            if (c->ou==1){
                if ((compare_name(dp,path, c)||compare_regex(dp,path,c)) || compare_size(path,c) || compare_date(path,c) || compare_dir(dp, path,c) || comparePerm(path,c) || compareCtc(path,c) || compare_mime(path,c)){
                    if (c->color != NULL && strcmp(c->color,"true")==0) printf("\033[1;33m");
                    printf("%s\n",path);
                }
            }
            
            else if ((compare_name(dp,path, c)||compare_regex(dp,path,c)) && compare_size(path,c) && compare_date(path,c) && compare_dir(dp, path,c) && comparePerm(path,c) && compareCtc(path,c) && compare_mime(path,c)){
                if (c->color != NULL && strcmp(c->color,"true")==0) printf("\033[1;33m");
                printf("%s\n",path);
            }
            parcours(path,c,count);
        }
        
    }
    closedir(dir); 
    

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
                    printf("\033[1;33m");
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
        if (c->ou==0){
        return 1;    
        }
        else if (c->ou==1){
            return 0;
        }
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
        if (c->ou==0){
        return 1;
        }
        else if (c->ou==1){
            return 0;
        }
    }

    else {
        if (isdir(cheminfichier)==1){
            return 0;
        }
        else{
        const char *str_request = dir->d_name;
        const char *str_regex = c->name;    
        if (regex(str_request,str_regex)==1){
            return 1;
        }
    }
    }   
    return 0;
}

int regex(const char* str_request,const char* str_regex){
    int err;
    regex_t preg;
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
    return 0;
}


int compare_size(char* chemin_fichier, struct_command* c){
    struct stat fichier;
    int plusmoins=0;
    int unite=0;
    if (c->size ==NULL){
        if (c->ou==0){
        return 1;
        }
        else if (c->ou==1){
            return 0;
        }
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
        if (c->ou==0){
        return 1;
        }
        else if (c->ou==1){
            return 0;
        }
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

int compare_mime(char* chemin_fichier, struct_command* c){
    //compare le mime type du fichier avec le mime type demandé

    if (c->mime==NULL){
        if (c->ou==0){
        return 1;
        }
        else if (c->ou==1){
            return 0;
        }
    }
    else {    
        const char* mime = getMegaMimeType(chemin_fichier);
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
    return 0;
}

int compare_dir(struct dirent *dir, char* testfichier, struct_command* c){
    if (c->yesdir==0){
        if (c->ou==0){
        return 1;
        }
        else if (c->ou==1){
            return 0;
        }
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

int comparePerm(char* chemin_fichier, struct_command* c){
    struct stat fichier;
    stat(chemin_fichier, &fichier);
    if (c->perm==NULL){
        if (c->ou==0){
        return 1;
        }
        else if (c->ou==1){
            return 0;
        }
    }
    if (isdir(chemin_fichier)==1){
        return 0;
    }
    else {
        int mode = fichier.st_mode;
        int octal = 0;
        int i = 1;
        while (mode != 0) {
            octal += (mode % 8) * i;
            mode /= 8;
            i *= 10;
        }
        int permasked=atoi(c->perm);
        if (octal==permasked){
            return 1;
        }
        else {
            return 0;
        }
    } 
    return 0;
}

int compareCtc(char* chemin_fichier, struct_command* c){
    if (c->ctc==NULL){
        if (c->ou==0){
        return 1;
        }
        else if (c->ou==1){
            return 0;
        }
    }
    if (isdir(chemin_fichier)==1){
        return 0;
    }
    else {
        FILE* fichier = fopen(chemin_fichier, "r");
        if (fichier!=NULL){
            char chaine[1000] = "";
            while (fgets(chaine, 1000, fichier) != NULL){
                const char *str_request = chaine;
                const char *str_search = c->ctc;
                if (regex(str_request, str_search)){
                    fclose(fichier);
                    return 1;
                }
            }
            fclose(fichier);
            return 0;
        }
        else {
            return 0;
        }
    }
    return 0;
}
