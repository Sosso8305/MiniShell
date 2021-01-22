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

    print_warning("à implémenter\n");
    return EXIT_SUCCESS;
}

int main (int argc, char * argv[]){
 
    return szouaoui(argc,argv);

}