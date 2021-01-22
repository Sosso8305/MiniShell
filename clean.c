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
        print_warning("command : clean <filename>  \n");
        return -1;
    }   
    

    int fd;
    if ((fd= open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) perror("open dest");
    close(fd);

    return EXIT_SUCCESS;
}

int main (int argc, char * argv[]){
 
    return szouaoui(argc,argv);

}