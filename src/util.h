#ifndef _UTIL_H_
#define _UTIL_H_
#include <dirent.h>
#include "struct_command.h"

void parcoursSimple(char* directory);
void parcours(char* directory,struct_command *c);
int compare(struct dirent *dir, struct_command* c);


#endif
