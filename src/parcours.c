#include <dirent.h>
#include <stdio.h>

void parcours(char* directory){
    struct dirent *dir;
    // opendir() renvoie un pointeur de type DIR. 
    DIR *d = opendir(directory); 
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //if (dir->d_type==)
            printf("%s type=%d\n", dir->d_name, dir->d_type);
        }
        closedir(d);
    }
}