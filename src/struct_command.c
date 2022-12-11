#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct_command.h"

struct_command* create_command(){
    struct_command* c = calloc(1,sizeof(struct_command));
    return c;
}

void destroy_command(struct_command *c){
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
    c->date=date;
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