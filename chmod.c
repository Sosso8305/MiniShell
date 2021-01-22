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

//    if(argc != 3){
//         print_warning("command : chmod <mode> <filename> \n");
//         return -1;
//     }

//     char * mode = "0";
//     strcat(mode,argv[1]);

//     int Realmode = strtol(mode, 0, 8);

//     if(chmod(argv[1], Realmode) == -1) {
// 		perror("chmod error");
// 		return EXIT_FAILURE;
// 	}

    print_warning("chmod non fonctionnel\n");
    return EXIT_SUCCESS;
}    

int main (int argc, char * argv[])
{
    return szouaoui(argc,argv);
 
}