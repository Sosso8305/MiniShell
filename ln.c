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

    if(argc != 3){
        print_warning("command : ln <src> <dest> \n");
        return -1;
    }

    if(symlink(argv[1],argv[2]) == -1) perror("symlink");    

    return EXIT_SUCCESS;
}

int main (int argc, char * argv[]){
 
    return szouaoui(argc,argv);

}