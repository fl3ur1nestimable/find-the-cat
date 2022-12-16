#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "struct_command.h"

int estuneoption(char *chaine){
    char* nomoption[] = {"-name", "-size", "-date", "-mime", "-ctc" ,"-dir", "-color", "-perm", "-link", "-threads", "-ou"};
    for (int i=0;i<11;i++){
        if (strcmp(chaine,nomoption[i])==0){ 
            return 1;
        }
    }
    return 0;
}


int main(int argc, char *argv[]){

    struct_command *c = create_command();

    if (argc < 2){
        printf("Pas assez d'argument\n");
        free(c);
        exit(EXIT_FAILURE);
    }

    if (argc < 3){
        parcoursSimple(argv[1],0);
        free(c);
        return 0;
    }

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
            
            else if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                printf("Le flag %s n'est pas correct\n",argv[i+1]);
                free(c);
                exit(EXIT_FAILURE);
            }

            else if (argv[i+2]!=NULL){
                printf("La valeur du flag %s est %s\n", argv[i+1],argv[i+2]);
                i=i+2;
            }
                        
            else {
                printf("Pas assez d'arguments\n");
                free(c);
                exit(EXIT_FAILURE);
            }

            if (i+2>=argc){
                free(c);
                return 1;
            }

        }

        else if (strcmp(argv[i],"-name")==0)
        {
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                setName(c,argv[i+1]);
                i++;
            }else
            {
                printf("-name : no value\n");
                free(c);
                exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[i],"-size")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0){
                setSize(c,argv[i+1]);
                i++;
            }
            else{
                printf("-size : no value\n");
                free(c);
                exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[i],"-date")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0){
                setDate(c,argv[i+1]);
                i++;
            }
            else{
                printf("-date : no value\n");
                free(c);
                exit(EXIT_FAILURE);
            }   
        }  

        else if (strcmp(argv[i],"-dir")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0){
                setDir(c,argv[i+1]);
                setYesDir(c);
                i++;
            }
            else if (argv[i+1]!=NULL && estuneoption(argv[i+1])==1){
                setYesDir(c);
            }
            else if(argv[i+1]==NULL){
                setYesDir(c);
            }
        }

        else if (strcmp(argv[i],"-mime")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                setMime(c,argv[i+1]);
                i++;
            }else
            {
                printf("-mime : no value\n");
                free(c);
                exit(EXIT_FAILURE);
            }
        }

        else if(strcmp(argv[i],"-perm")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                setPerm(c,argv[i+1]);
                i++;
            }else
            {
                printf("-perm : no value\n");
                free(c);
                exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[i],"-ctc")==0)
        {
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                setCtc(c,argv[i+1]);
                i++;
            }else
            {
                printf("-ctc : no value\n");
                free(c);
                exit(EXIT_FAILURE);
            }
        }

        
        
    }

    parcours(argv[1],c,0);
    free(c);
    return 0;
}

