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
int append = 0;

void init_msg(){
    puts("\n***************************************");
    puts( "\n   MINI SHELL \n  \t\t by Zouaoui Sofiane\n"); 
    puts("***************************************\n");

}

void print_warning(char * text){
    printf("\x1B[31m");
    printf("%s",text);
    printf("\x1B[0m");
}


void pwd(int saut){
    char * tmp;
    tmp = malloc(BUFSIZE*sizeof(char));
    if (getcwd(tmp,BUFSIZE) == NULL)  perror("getcwd");
    
    if(saut)
        printf("%s \n",tmp);
    else{
        printf("\x1B[36m");
        printf("%s",tmp);
        printf("\x1B[0m");
    }
}

int cd(char ** arg){

    if(arg[1] == NULL)
        print_warning("command: cd <directory floder> \n");
    else
        if(chdir(arg[1])==-1) perror("chdir");

    return 0;
}

int read_command(char * command, char ** arg){
    int nb_arg = 1;
    char * chaine;

    //read command
    scanf("%s",command);


    //exit
    if(strcmp(command,"exit") == 0 ) return -1;

    //read arg
    while(getchar() != '\n'){
        chaine= malloc((BUFSIZE -1) * sizeof(char));
        scanf("%s",chaine);
        

        if (!strcmp(chaine,">") || !strcmp(chaine,">>")){
            fdest = malloc((BUFSIZE -1) * sizeof(char));
            scanf("%s",fdest);
            if(!strcmp(chaine,">>")){
                append = 1;
            }

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


    if((pid = fork()) == -1 ) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
                
    if (pid == 0){
        //fils
        
        if(fdest){

            if(append) 
                outfd=open(fdest,O_WRONLY | O_CREAT | O_APPEND, 0666);
            else 
                outfd=open(fdest,O_WRONLY | O_CREAT | O_TRUNC, 0666);

            if(outfd == -1) perror ("open fdest");

            dup2(outfd,STDOUT_FILENO);
        }

        if(!strcmp(command,"cd")) cd(arg);

        else if (!strcmp(command,"pwd")) pwd(1);

        else if(execvp(command,arg) == -1) perror("execvp");

        if(fdest) close(outfd);

    }
    else{
        wait(&pid);
        if (WIFEXITED(pid)) return EXIT_SUCCESS;
        return EXIT_FAILURE;
    }



    return EXIT_SUCCESS;

}

void shell(){
    printf("\033[0;35m");
    printf("sosso@shell:");
    printf("\033[0m");
    pwd(0);
    printf("$ ");

}

int main(int argc, char const *argv[])
{

    char command[BUFSIZE];
    char * arg[BUFSIZE];
    int nb_arg;

    init_msg();

    while(1){
        fdest = NULL;

        shell();
        
        if ((nb_arg = read_command(command,arg)) == -1){
            printf("\033[0;33m");
            puts("End of my shell");
            printf("\033[0m");
            break;        //la commande exit s'est bien executé
        }
        arg[0] = command;


        if (DEBUG){
            printf("commande a exécuter: %s, %d arguments [",command,nb_arg);
            for(int i= 0;i<nb_arg;i++){
                printf("%i:%s,",i,arg[i]);
            }
            printf("], fdest : %s\n",fdest);
        }
        

        if (run_command(command,arg) == -1) perror("run commande error");

        
        
    }


    return 0;
}
