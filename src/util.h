#ifndef _UTIL_H_
#define _UTIL_H_
#include <dirent.h>
#include "struct_command.h"

void parcoursSimple(char* directorypath,int count);
void parcours(char* directorypath,struct_command *c/*,int count*/);
int compare_name(struct dirent *dir, char* cheminfichier, struct_command* c);
int compare_regex(struct dirent *dir, char* cheminfihcier, struct_command* c);
int compare_size(char* chemin_fichier, struct_command* c);
int compare_date(char* chemin_fichier, struct_command* c);
int compare_mime(char* chemin_fichier, struct_command* c);
int compare_dir(struct dirent *dir, char* testfichier, struct_command* c);
int isdir(char* chemin_fichier);


#endif
