#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

void print_warning(char * text){
    printf("\x1B[31m");
    printf("%s",text);
    printf("\x1B[0m");
}

int szouaoui(int argc,char * argv[]){
    if(argc != 3){
        print_warning("command : mv <src> <dest> \n");
        return -1;
    }   

    int fdsrc,fddest;
    char buf[BUFSIZE];
    int caract;

    if ( (fdsrc = open(argv[1],O_RDONLY)) == -1) perror("open src");

    if ( (fddest = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) perror("open dest");

    while ( (caract = read(fdsrc,buf,BUFSIZE)) ){
        write(fddest,buf,caract);
    }

    close(fddest);
    close(fdsrc);

    if (remove(argv[1]) == -1) perror("remove src");

    return EXIT_SUCCESS;

}

int main (int argc, char * argv[]){
 
    return szouaoui(argc,argv);

}