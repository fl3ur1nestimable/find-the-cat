#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

int estuneoption(char *chaine){
    char* nomoption[] = {"-name", "-size", "-date", "-mime", "-ctc" ,"-dir", "-color", "-perm", "-link", "-threads", "-ou"};
    for (int i=0;i<11;i++){
        if (strcmp(chaine,nomoption[i])==0){
            return 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{
    
    // int* paramoption = {1, 1, 1, 1, 1, 2};
    if (argc < 2){
        printf("Pas assez d'argument\n");
        return 0;
    }

    parcours(argv[1]);

    for (int i=2;i<argc;i++){
        if (strcmp(argv[i],"-test")==0 && argv[i+1]!=NULL){
            if (strcmp(argv[i+1],"-dir")==0){
                if (argv[i+2]!=NULL){
                    if (estuneoption(argv[i+2])==1){
                        printf("La valeur du flag -dir est nulle\n");
                        i=i+1;
                    }
                    else {
                        printf("La valeur du flag -dir est %s\n", argv[i+2]);
                        i=i+2;
                    }
                }
                else {
                    printf("La valeur du flag -dir est nulle\n");
                    i=i+1;
                }
            }

            else if (strcmp(argv[i+1],"-link")==0 || strcmp(argv[i+1],"-color")==0 || strcmp(argv[i+1],"-ou")==0){
                printf("La valeur du flag %s est nulle\n", argv[i+1]);
                i=i+1;
            }


            
            else if (argv[i+2]!=NULL){
                printf("La valeur du flag %s est %s\n", argv[i+1],argv[i+2]);
                i=i+2;
            }
            
            else {
                printf("Pas assez d'arguments\n");
            }
        }

    }
    return 0;
}
