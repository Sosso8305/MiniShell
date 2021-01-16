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

int main (int argc, char * argv[]){
 
    if(argc != 2){
        print_warning("command : rm <filename> \n");
        return -1;
    }   

    if (remove(argv[1]) == -1) perror("remove src");

}