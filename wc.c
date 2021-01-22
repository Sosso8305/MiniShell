#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void print_warning(char * text){
    printf("\x1B[31m");
    printf("%s",text);
    printf("\x1B[0m");
}

int szouaoui(int argc,char * argv[]){
    if(argc != 2){
        print_warning("command : wc <src> \n");
        return -1;
    }   

    FILE * file;
    char caract;
    int nb = 0;

    

    if((file = fopen(argv[1],"r")) == NULL) perror("fopen file");

    while ((caract = getc(file)) != EOF){
        if (caract=='\n') nb++;
    }
    
    printf("%s contient %i lignes \n",argv[1],nb+1);

    fclose(file);
    return EXIT_SUCCESS;
}

int main (int argc, char * argv[]){
 
    return szouaoui(argc,argv);

}