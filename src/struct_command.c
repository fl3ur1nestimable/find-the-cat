#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct_command.h"

struct_command* create_command(){
    struct_command* c = calloc(1,sizeof(struct_command));
    return c;
}

/*void destroy_command(struct_command *c){
    free(c);
}*/

void setName(struct_command* c, char* name){
    c->name=name;
    c->nb_of_flags++;
}

void setSize(struct struct_command* c, char* size){
    c->size=size;
    c->nb_of_flags++;
}
