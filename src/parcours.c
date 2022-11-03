#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void parcours(char* directory){
    struct dirent *dir;
    // opendir() renvoie un pointeur de type DIR. 
    DIR *d = opendir(directory); 
    printf("BONSOIR\n");
    if (d)
    {
        printf("id\n");
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type==4 && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
                parcours(dir->d_name); //ici ça va pas parce qu'il faut concaténer chemin d'avant et nouveau dossier genre ./cheminavant/cheminapres la y a que cheminapres
            }
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}
