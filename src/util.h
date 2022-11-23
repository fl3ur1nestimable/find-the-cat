#ifndef _UTIL_H_
#define _UTIL_H_
#include <dirent.h>
#include "struct_command.h"


void parcours(char* directory,struct_command *c);
int compareName(struct dirent *dir, char* name);


#endif
