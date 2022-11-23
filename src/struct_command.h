#ifndef STRUCT_COMMAND_H
#define STRUCT_COMMAND_H

typedef struct struct_command
{
    char *name;
    char *size;
    char *date;
    char *mime;
    char *ctc;
    char *dir;
    char *color;
    char *perm;
    char *link;
    char *threads;
    char *ou;
} struct_command;

struct_command* create_command();
//void destroy_command(struct_command *c);
void setName();


#endif
