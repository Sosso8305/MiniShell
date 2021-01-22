#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<errno.h>
//author ZOUAOUI_Sofiane

void print_stat(const char *ref, struct stat *data){

	struct passwd *pw;
	struct group *gr;
	char type;
	#define LTEMPS 32
	char pws[9], grs[9], temps[LTEMPS];
	type = '?';
	int m =data->st_mode;

	if (S_ISREG(data->st_mode)) type ='-';
	else if (S_ISDIR(data->st_mode)) type ='d';
	else if (S_ISBLK(data->st_mode)) type ='b';
	else if (S_ISFIFO(data->st_mode)) type ='p';
	else if (S_ISCHR(data->st_mode)) type ='c';
	else if (S_ISLNK(data->st_mode)) type ='l';

	strftime(temps,LTEMPS,"%h.  %e %H:%M", localtime(&(data->st_mtime)));    


	pw = getpwuid(data->st_uid);
	
	if (pw!=NULL) strcpy(pws,pw->pw_name);
	else sprintf(pws,"%8d", (int)data->st_uid);


	gr = getgrgid(data->st_gid);
	
	if (gr!=NULL) strcpy(grs,gr->gr_name);
	else sprintf(grs,"%8d", (int)data->st_gid);

	if (S_ISLNK(data->st_mode)) {
		char namelink[1024];
		ssize_t len;
		if ((len = readlink(ref,namelink,sizeof(namelink)-1)) != -1)
			namelink[len] = '\0';
		else {
			perror("readlink()");
			strcpy(namelink,"erreur sur la profondeur =p");
		}
		
		printf("lrwxrwxrwx %2d %8s %8s %9d %s %s -> %s \n",
		(int)data->st_nlink, pws, grs, (int)data->st_size,temps,ref,namelink);

	}

	else printf("%c%c%c%c%c%c%c%c%c%c %2d %8s %8s %9d %s %s\n",
		type,
		m&S_IRUSR ?'r':'-',
		m&S_IWUSR ?'w':'-',
		m&S_IXUSR ?'x':'-',
		m&S_IRGRP ?'r':'-',
		m&S_IWGRP ?'w':'-',
		m&S_IXGRP ?'x':'-',
		m&S_IROTH ?'r':'-',
		m&S_IWOTH ?'w':'-',
		m&S_IXOTH ?'x':'-',
		(int)data->st_nlink, pws, grs, (int)data->st_size,temps,ref);
}


void local(const char * name) { //fct pour l'exo 9  je suis conscient que je repte ce que j'ai deja ecrit dans le main
	struct stat data;
	DIR * dirp; 
	struct dirent * dp;
	if ((dirp = opendir(name)) == NULL) 
		perror("err1 don't open file"); 
	while ((dp = readdir(dirp))) {
		if (dp->d_name[0] != '.'){  // pour cacher les fichier speciaux
			if ( lstat(dp->d_name,&data) == 1 ) {
				fprintf(stderr,"err2 satatut pour %s\n",dp->d_name);
				continue; 
		    	}
		    	else{ 
		        	print_stat(dp->d_name,&data);
            		}
	    	}
    	}
	if (errno != 0) 
		perror("error reading");
	else 
		closedir(dirp);    
}

int szouaoui(int argc,char * argv[]){

	struct stat data;
	DIR *dirp;
	struct dirent *dp;
	char temp[512];
	


	if(argc < 2) local(".");

	else {

	
		for(int i = 1; i<argc; i++){
			if( lstat(argv[i],&data) == -1){
				fprintf(stderr,"%s: err1 satatut pour %s\n",argv[0],argv[i]);
				continue;
			}
			if(S_ISDIR(data.st_mode)){
				if((dirp = opendir(argv[i]) )== NULL){
					perror("don't open directory");
					return 0;
				 }
				
				while((dp=readdir(dirp))){
					sprintf(temp,"%s/%s",argv[i],dp->d_name);
					if( lstat(temp,&data) == -1){
						fprintf(stderr,"%s: err2 satatut pour %s\n",argv[0],dp->d_name);
						continue;
					}
					print_stat(dp->d_name,&data);
				}
				closedir(dirp);

			}
			else print_stat(argv[i],&data);
		}	

	}
	return EXIT_SUCCESS;
}




int main(int argc, char * argv[]){
	
	return szouaoui(argc,argv);
	

}



