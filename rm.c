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

int szouaoui(int argc,char *argv[]){
   if(argc != 2){
        print_warning("command : rm <filename> \n");
        return -1;
    }   

    struct stat data;

    if(lstat(argv[1],&data) == -1) perror("lstat");


    if (S_ISREG(data.st_mode)){
        if (unlink(argv[1]) == -1) perror("unlink src");
    }
    else print_warning("arg : it's not a file\n");
    
    return EXIT_SUCCESS;

}    

int main (int argc, char * argv[])
{
    return szouaoui(argc,argv);
 
}