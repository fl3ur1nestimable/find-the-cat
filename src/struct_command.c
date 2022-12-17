#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct_command.h"

struct_command* create_command(){
    struct_command* c = calloc(1,sizeof(struct_command));
    return c;
}

void destroy_command(struct_command *c){
    free(c->perm);
    free(c->date);
    free(c);
}

void setName(struct_command* c, char* name){
    c->name=name;
    c->nb_of_flags++;
}

void setSize(struct struct_command* c, char* size){
    c->size=size;
    c->nb_of_flags++;
}

void setDate(struct struct_command* c, char* date){
    int n = (int)strlen(date);
    c->date = malloc((n+1)*sizeof(char));
    strcpy(c->date,date);
    c->nb_of_flags++;
}

void setMime(struct struct_command* c, char* mime){
    c->mime=mime;
    c->nb_of_flags++;
}

void setDir(struct struct_command* c, char* dir){
    c->dir=dir;
    c->nb_of_flags++;
}

void setYesDir(struct struct_command* c){
    c->yesdir=1;
}

void setPerm(struct struct_command* c, char* perm){
    char *perm2 = malloc(10*sizeof(char));
    strcpy(perm2,"100");
    strcat(perm2,perm);
    c->perm=malloc(10*sizeof(char));
    strcpy(c->perm,perm2);
    c->nb_of_flags++;
    free(perm2);
}

void setOu(struct struct_command* c){
    c->ou=1;
    c->nb_of_flags++;
}

void setCtc(struct struct_command* c, char* ctc){
    c->ctc=ctc;
    c->nb_of_flags++;
}

void setColor(struct struct_command* c){
    c->color="true";
    c->nb_of_flags++;
}
