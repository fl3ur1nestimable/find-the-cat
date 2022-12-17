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
    int yesdir;
    char *color;
    char *perm;
    char *link;
    char *threads;
    int ou;
    int nb_of_flags;
} struct_command;

struct_command* create_command();
void destroy_command(struct_command *c);
void setName(struct_command* c, char* name);
void setSize(struct struct_command* c, char* size);
void setDate(struct struct_command* c, char* date);
void setMime(struct struct_command* c, char* mime);
void setDir(struct struct_command* c, char* dir);
void setYesDir(struct struct_command* c);
void setPerm(struct struct_command* c, char* perm);
void setOu(struct struct_command* c);
void setCtc(struct struct_command* c, char* ctc);
void setColor(struct struct_command* c);


#endif
