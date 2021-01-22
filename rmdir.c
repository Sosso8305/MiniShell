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
    if(argc != 2){
        print_warning("command : rmdir <directory name> \n");
        return -1;
    }   


    struct stat data;

    if(lstat(argv[1],&data) == -1) perror("lstat");


    if (S_ISDIR(data.st_mode)){
        if (rmdir(argv[1]) == -1) perror("rmdir src");
    }
    else print_warning("arg : it's not directory \n");
    
    return EXIT_SUCCESS;

}

int main (int argc, char * argv[]){

    return szouaoui(argc,argv);

}