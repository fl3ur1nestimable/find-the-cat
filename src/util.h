#ifndef _UTIL_H_
#define _UTIL_H_
#include <dirent.h>
#include "struct_command.h"

void parcoursSimple(char* directory,int count);
void parcours(char* directory,struct_command *c);
int compare_name(struct dirent *dir, struct_command* c);
int compare_size(char* chemin_fichier, struct_command* c);


#endif
