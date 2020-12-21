#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>


#define BUFSIZE 512

char * fdest = NULL;

int read_command(char * command, char ** arg){
    char chaine[BUFSIZE];
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
    pid_t pid;
    int outfd;

    if((pid = fork()) == -1 ) perror("fork");
        


    if (pid == 0){
        //fils

        if(fdest){
            if((outfd=open(fdest,O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) perror ("open fdest");
            dup2(outfd,STDOUT_FILENO);
        }

        if(execv(command,arg) == -1) perror("execv");

        if(fdest) close(outfd);

    }
    else{
        wait(&pid);
        if (WIFEXITED(pid)) return EXIT_SUCCESS;
        return EXIT_FAILURE;
    }



    return EXIT_SUCCESS;

}



int main(int argc, char const *argv[])
{

    char command[BUFSIZE];
    char * arg[BUFSIZE];
    int nb_arg;

    while(1){
        fdest = NULL;
        printf("sosso@shell $ ");
        
        if ((nb_arg = read_command(command,arg)) == -1) return EXIT_SUCCESS;         //la commande exit c'est bien executé
        arg[0]=command;

        if (run_command(command,arg) == -1) perror("run commande");

    }


    return 0;
}
