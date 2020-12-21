#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFSIZE 512

int read_command(char * command, char ** arg){
    char chaine[BUFSIZE];
    char fdest[BUFSIZE];
    int nb_arg;

    //read command
    scanf("%s",command);

    //exit
    if(strcmp(command,"exit") == 0 ) return -1;

    //read arg
    while(getchar() != '\n'){
        scanf("%s",chaine);

        if (!strcmp(chaine,">")){
            scanf("%s",fdest);

        }
        else arg[nb_arg++]=chaine;
    }

    arg[nb_arg] = NULL;
    return nb_arg;

}


int run_command(char * command, char ** arg){
    
}



int main(int argc, char const *argv[])
{
    




    return 0;
}
