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
    if(argc < 2){
        print_warning("command : cat <filename1> ... <filenameN> \n");
        return -1;
    }   

    FILE * file;
    char caract;

    for (int i = 1; i<argc; i++){

        if ( (file = fopen(argv[i],"r")) == NULL) perror("fopen file");

        while ((caract = getc(file)) != EOF){
            printf("%c",caract);
        }

        fclose(file);
    }

    return EXIT_SUCCESS;


}



int main (int argc, char * argv[]){
 
    return szouaoui(argc,argv);    
}
    