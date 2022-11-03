#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int estuneoption(char *chaine){
    char* nomoption[] = {"-name", "-size", "-date", "-mime", "-ctc" ,"-dir"};
    for (int i=0;i<6;i++){
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

    for (int i=1;i<argc;i++){
        if (strcmp(argv[i],"-test")==0 && argv[i+1]!=NULL){
            if (strcmp(argv[i+1],"-dir")==0){
                if (argv[i+2]!=NULL){
                    if (estuneoption(argv[i+2])==1){
                        printf("La valeur du flag -dir est nulle\n");
                    }
                    else {
                        printf("La valeur du flag -dir est %s\n", argv[i+2]);
                    }
                }
                else {
                    printf("La valeur du flag -dir est nulle\n");
                }
            }
            else if (argv[i+2]!=NULL){
                printf("La valeur du flag %s est %s\n", argv[i+1],argv[i+2]);
            }
            else {
                printf("Pas assez d'arguments\n");
            }
        }
    }
    return 0;    
}
    


