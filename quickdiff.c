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
        print_warning("command : quickdiff <src1> <src2> \n");
        return -1;
    }



    char ligne1[BUFSIZE];
    char ligne2[BUFSIZE];

    int fd1,fd2;

    if ( (fd1 = open(argv[1],O_RDONLY)) == -1) perror("open src1");
    if ( (fd2 = open(argv[2],O_RDONLY)) == -1) perror("open src2");

    
    int size1,size2;

    char c1[2];
    char c2[2];

    while ((size1 = read(fd1,c1,1)) && (size2 = read(fd2,c2,1))){
        
        

        strcat(ligne1,c1);
        strcat(ligne2,c2);
        

        if(c1[0] == '\n' || c2[0] =='\n'){
            // if(c1[0] == '\n'){
            //     while(c2[0] =='\n'){
            //         read(fd2,c2,1);
            //         strcat(ligne2,c2);
            //     }
            // }
            // else{
            //     while(c1[0] == '\n'){
            //         read(fd1,c1,1);
            //         strcat(ligne1,c1);
            //     }

            // }

            if (!strcmp(ligne1,ligne2)){
                puts("ok");
            }
            else 
            printf("ligne differente:\n%s --> %s \n%s --> %s \n \n",argv[1],ligne1,argv[2],ligne2);
            
            bzero(ligne1,BUFSIZE);
            bzero(ligne2,BUFSIZE);
            
        }


    }

    close(fd1);
    close(fd2);
    puts("marche pas encore trés bien")

    return EXIT_SUCCESS;
}

int main (int argc, char * argv[]){
 
    return szouaoui(argc,argv);

}