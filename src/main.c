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

void arcenciel(){
    //draw a rainbow flag
    printf("\033[1;31m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\033[1;33m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\033[1;32m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\033[1;36m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\033[1;34m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\033[1;35m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\033[1;37m");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("\033[0m");
    printf("\n");

    //draw a rainbow text
    printf("\033[1;31m");
    printf("  _______  _______  _______  _______  _______  _______  _______  _______  _______  _______  _______  _______  _______ \n");
    printf("\033[1;33m");
    printf(" |       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       |\n");
    printf("\033[1;32m");
    printf(" |   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   ||   _   |\n");
    printf("\033[1;36m");
    printf(" |  | |  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  ||  |_|  |\n");
    printf("\033[1;34m");
    printf(" |  |_|  ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       |\n");
    printf("\033[1;35m");
    printf(" |       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       ||       |\n");
    printf("\033[1;37m");
    printf(" |_______||_______||_______||_______||_______||_______||_______||_______||_______||_______||_______||_______||_______|\n");
    printf("\033[0m");
    printf("\n");

    //draw a cat with rainbow colors
    printf("\033[1;31m");
    printf("  /\\_/\\ \n");
    printf("\033[1;33m");
    printf(" ( o.o )\n");
    printf("\033[1;32m");
    printf("  > ^ < \n");
    printf("\033[1;36m");
    printf(" /     \\\n");
    printf("\033[1;34m");
    printf("/| | | |\\\n");
    printf("\033[1;35m");
    printf("  | | | \n");
    printf("\033[1;37m");
    printf("  | | | \n");
    printf("\033[0m");
    printf("\n");

}

int main(int argc, char *argv[]){

    struct_command *c = create_command();

    if (argc < 2){
        printf("Pas assez d'argument\n");
        destroy_command(c);;
        exit(EXIT_FAILURE);
    }

    if (argc < 3){
        parcoursSimple(argv[1],0);
        destroy_command(c);;
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
                destroy_command(c);;
                exit(EXIT_FAILURE);
            }

            else if (argv[i+2]!=NULL){
                printf("La valeur du flag %s est %s\n", argv[i+1],argv[i+2]);
                i=i+2;
            }
                        
            else {
                printf("Pas assez d'arguments\n");
                destroy_command(c);;
                exit(EXIT_FAILURE);
            }

            if (i+2>=argc){
                destroy_command(c);;
                return 1;
            }

        }

        else if (strcmp(argv[i],"-name")==0)
        {
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                if (c->name==NULL){
                    setName(c,argv[i+1]);
                    i++;
                }
                else{
                    printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                    exit(EXIT_FAILURE);
                }
            }else
            {
                printf("-name : no value\n");
                destroy_command(c);;
                exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[i],"-size")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0){
                if (c->size==NULL){
                    setSize(c,argv[i+1]);
                    i++;
                }
                else{
                    printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                printf("-size : no value\n");
                destroy_command(c);;
                exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[i],"-date")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0){
                if(c->date==NULL){
                setDate(c,argv[i+1]);
                i++;
                }
                else {
                    printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                printf("-date : no value\n");
                destroy_command(c);;
                exit(EXIT_FAILURE);
            }   
        }  

        else if (strcmp(argv[i],"-dir")==0){
            if (c->yesdir==0){
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
            else {
                    printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                    exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[i],"-mime")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                if (c->mime==NULL){
                setMime(c,argv[i+1]);
                i++;
                }
                else{
                    printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                    exit(EXIT_FAILURE);
                }
            }else
            {
                printf("-mime : no value\n");
                destroy_command(c);;
                exit(EXIT_FAILURE);
            }
        }

        else if(strcmp(argv[i],"-perm")==0){
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                if (c->perm==NULL){
                setPerm(c,argv[i+1]);
                i++;
                }
                else{
                    printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                    exit(EXIT_FAILURE);
                }
            }else
            {
                printf("-perm : no value\n");
                destroy_command(c);;
                exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[i],"-ctc")==0)
        {
            if (argv[i+1]!=NULL && estuneoption(argv[i+1])==0)
            {
                if (c->ctc==NULL){
                setCtc(c,argv[i+1]);
                i++;
                }
                else{
                    printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                    exit(EXIT_FAILURE);
                }
            }else
            {
                printf("-ctc : no value\n");
                destroy_command(c);;
                exit(EXIT_FAILURE);
            }
        }

        else if( strcmp(argv[i],"-color")==0){
            if (c->color==0){
                setColor(c);
            }
            else{
                printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                exit(EXIT_FAILURE);
            }
            
        }

        else if (strcmp(argv[i],"-ou")==0){
            if (c->ou==0){
                setOu(c);
            }
            else {
                printf("Vous ne pouvez pas utiliser 2 fois la même option\n");
                exit(EXIT_FAILURE);
            }
        }

        else if (strcmp(argv[i],"-cat")==0){
            //draw nyancat in the terminal
            arcenciel();
            exit(EXIT_SUCCESS);
            
        }

        else
        {
            printf("%s :not a valid flag\n",argv[i]);
            exit(EXIT_FAILURE);
        }
        

        
        
    }

    parcours(argv[1],c,0);
    destroy_command(c);;
    return 0;
}

