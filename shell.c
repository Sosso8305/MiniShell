#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>


#define BUFSIZE 512
#define DEBUG 0

char * fdest = NULL;

int read_command(char * command, char ** arg){
    int nb_arg;
    char * chaine;

    //read command
    scanf("%s",command);

    //exit
    if(strcmp(command,"exit") == 0 ) return -1;

    //read arg
    while(getchar() != '\n'){
        chaine= malloc((BUFSIZE -1) * sizeof(char));
        scanf("%s",chaine);
        

        if (!strcmp(chaine,">")){
            fdest = malloc((BUFSIZE -1) * sizeof(char));
            scanf("%s",fdest);

            break;

        }
        else arg[nb_arg++]=chaine;
    }

    arg[nb_arg] = NULL;
    return nb_arg;

}


int run_command(char * command, char ** arg){
    pid_t pid;
    int outfd;

    if(DEBUG){
        for(int i= 0;i<sizeof(arg);i++){
            printf("arg n° %i %s \n",i,arg[i]);
        }
    }


    if((pid = fork()) == -1 ) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
                
    if (pid == 0){
        //fils
        
        if(fdest){
            if((outfd=open(fdest,O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) perror ("open fdest");
            dup2(outfd,STDOUT_FILENO);
        }

        if(execvp(command,arg) == -1) perror("execvp");

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
        
        if ((nb_arg = read_command(command,arg)) == -1){
            puts("End of my shell");
            return EXIT_SUCCESS;         //la commande exit s'est bien executé
        }

        if (DEBUG){
            printf("commande a exécuter: %s, %d arguments [",command,nb_arg);
            for(int i= 0;i<nb_arg;i++){
                printf("%i:%s,",i,arg[i]);
            }
            printf("], fdest : %s\n",fdest);
        }
        

        if (run_command(command,arg) == -1) perror("run commande error");

        //arg[1] 
        
    }


    return 0;
}
