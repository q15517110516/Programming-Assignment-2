//#include <stdio.h>
//#include <string.h>
//#include <strings.h>
//#include <limits.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <pwd.h>
//#include <dirent.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <signal.h>
//#include "sh.h"
//#include <fcntl.h>
//#include <sys/stat.h>
//#include <errno.h>
//#include <grp.h>
//#include <time.h>
//
//extern char** environ;	
//int sh(int argc, char **argv, char **envp)
//{
//	
//	char *prompt = calloc(PROMPTMAX, sizeof(char));
//	char *commandline = calloc(MAX_CANON, sizeof(char));
//	char *command, *arg, *commandpath, *p, *pwd, *owd;
//	char **args = calloc(MAXARGS, sizeof(char*));
//	int uid, i, status, argsct, go = 1;
//	char **prePath = malloc(MAXARGS*sizeof(char*));//store 10 past pathes
//    int NumofPath = 0;
//	size_t bufsize = 0;
//	struct passwd *password_entry;
//	char *homedir;
//	struct pathelement *pathlist;
//	int count = 0;
//	uid = getuid();
//	password_entry = getpwuid(uid);               /* get passwd info */
//	homedir = password_entry->pw_dir;		/* Home directory to start
//							out with*/
//
//	if ((pwd = getcwd(NULL, PATH_MAX + 1)) == NULL)
//	{
//		perror("getcwd");
//		exit(2);
//	}
//	owd = calloc(strlen(pwd) + 1, sizeof(char));
//	memcpy(owd, pwd, strlen(pwd));
//	prompt[0] = ' '; prompt[1] = '\0';
//	
//
//	/* Put PATH into a linked list */
//	pathlist = get_path();
//	
//	while (go)
//	{
//		pathlist = get_path();
//		/* print your prompt */
//		do {
//            fprintf(stdout,"%s[%s]>>",prompt,cwd());
//        } while ((getline(&commandline, &bufsize, stdin) == 1) && (commandline[strlen(commandline)-1] == '\n'));
//
//		count = 0;
//
//		if (commandline[strlen(commandline)-1] == '\n'){
//            commandline[strlen(commandline)-1] = '\0';
//        }
//		arg = strtok(commandline, " ");
//		i=0;
//		command = arg;
//		while(arg){
//			args[i] = arg;
//			count++;
//			arg = strtok(NULL, " ");
//			i++;
//		}
//		args[i] = NULL;
//		/* get command line and process */
//
//		/* check for each built in command and implement */
//		
//		 /*  else  program to exec */
//		if(strcmp(args[0], "exit") == 0){
//			exit(0);
//		}
//		if(strcmp(args[0], "which") == 0){
//			pathlist = get_path();
//			printf("%s\n", which(args[1], pathlist));
//		}
//		if(strcmp(args[0], "where") == 0){
//			pathlist = get_path();
//			printf("%s\n", which(args[1], pathlist));
//		}
//		if(strcmp(args[0], "cd") == 0 ){
//			mycd(args[1], prePath, &NumofPath);
//		}
//		
//		if(strcmp(args[0], "pwd") == 0){
//			printf("%s\n", cwd());
//		}
//		if(strcmp(args[0], "list") == 0){
//			list(args);
//		}
//		if(strcmp(args[0], "pid") == 0){
//			printf("PID: %d\n" , getpid());
//			
//		}
//		
//		if(strcmp(args[0], "kill") == 0){
//			if (count = 2){
//				kill(args[1], SIGTERM);
//			}
//			if(count = 3){
//				int sig =0;
//				if(args[2][0] = '-'){
//					sscanf(args[2],"%(1-9)", args[2]);
//					sig = atoi(args[2]);
//					kill(args[1], sig);
//				}
//				else{
//					sig = atoi(args[2]);
//					kill(args[1],sig);
//				}
//			}
//			
//			
//		}
//		if(strcmp(args[0], "prompt") == 0){
//			if(count = 1){
//				printf("input prompt prefix:");
//				while(1){
//					if(fgets(commandline, 1024, stdin) == NULL){
//						continue;
//					}
//					else{
//						commandline[strlen(commandline)-1] = '\0';
//						strcpy(prompt, commandline);
//						break;
//					}
//				}
//			}
//			else{
//				strcpy(prompt, args[1]);
//			}
//			
//		}
//		if(strcmp(args[0], "printenv") == 0){
//			int index = 0;
//			if(args[1] == NULL){
//				for(index =0; environ[index]!=NULL; index++){
//					printf("%s\n", environ[index]);
//				}
//			}
//			else if(args[2] == NULL){
//				fprintf(stdout,"%s\n",getenv(args[1]));
//			}
//			else{
//				fprintf(stderr,"More than 2 arguments provided.\n");
//			}
//		}
//		if(strcmp(args[0], "setenv") == 0){
//			int index =0;
//			if(args[1] == NULL){
//				for(index =0; environ[index]!=NULL; index++){
//					printf("%s\n", environ[index]);
//				}
//			}
//			else if(args[2] == NULL){
//				setenv(args[1],"",0);
//			}
//			else if(args[3] == NULL){
//				setenv(args[1],args[2],1);
//			}
//			else {
//				printf(stderr, "More than 3 arguments provided.\n");
//			}
//		}
//		
//			
//			
//			/* find it */
//			/* do fork(), execve() and waitpid() */
//	}
//
//	return 0;
//} /* sh() */
//
//
//void mycd (char *mycd,char **prePath,int *NumofPath){
//    prePath[*NumofPath] = cwd();
//    if(mycd == NULL){
//        chdir(getenv("HOME"));
//        *NumofPath += 1;
//    }else if(strcmp(mycd,"-") == 0){
//        if(*NumofPath == 0){
//            fprintf(stdout,"No previus path travel history\n");
//        }else{
//            prePath[*NumofPath] = NULL;
//            chdir(prePath[*NumofPath-1]);
//            *NumofPath -= 1;
//        }
//    }else if(chdir(mycd) != -1){
//        *NumofPath += 1;
//    }else if(chdir(mycd) == -1){
//        fprintf(stdout,"invalid directory\n");
//        prePath[*NumofPath] = NULL;
//    }
//}
//char *which(char *command, struct pathelement *pathlist)
//{
//	char cmd[64];
//	char* tmp = calloc(PROMPTMAX, sizeof(char));
//	while (pathlist) {
//		sprintf(cmd, "%s/%s", pathlist->element, command);
//		if (access(cmd, X_OK) == 0) {
//			printf("[%s]\n", cmd);
//			tmp = cmd;
//			return tmp;
//		}
//		pathlist = pathlist->next;
//	}
//	printf(stdout, "[%s] not found\n", command);
//	return NULL;
//	/* loop through pathlist until finding command and return it.  Return
//	NULL when not found. */
//
//} /* which() */
//
//char *where(char *command, struct pathelement *pathlist)
//{
//	int flag = 0;
//	char cmd[64] ;
//	char* tmp = calloc(PROMPTMAX, sizeof(char));
//	while (pathlist) {
//		sprintf(cmd, "%s/%s", pathlist->element, command);
//		if (access(cmd, X_OK) == 0) {
//			printf("[%s]\n", cmd);
//			tmp = cmd;
//			flag = 1;
//		}
//		pathlist = pathlist->next;
//	}
//	if (flag) {
//		return tmp;
//	}
//	fprintf(stdout, "[%s] not found\n", command);
//	
//	return NULL;
//	/* similarly loop through finding all locations of command */
//} /* where() */
//
//char* cwd(){
//	
//	char *ccwd;
//	ccwd = getcwd(NULL, 0);
//	return ccwd;
//}
//
//void list(char **args)
//{
//	
//
//  struct passwd *pw;
//  struct group *gp;
//  DIR *mydir;
//  char *c;
//  int i;
//  struct dirent *myfile;
//  struct stat File_Stat;
//  mydir=opendir(".");
//  stat(".",&File_Stat); 
//  while((myfile=readdir(mydir))!=NULL)
//  {
//    stat(myfile->d_name,&File_Stat);  
//    printf( (S_ISDIR(File_Stat.st_mode)) ? "d" : "-");
//    printf( (File_Stat.st_mode & S_IRUSR) ? "r" : "-");
//    printf( (File_Stat.st_mode & S_IWUSR) ? "w" : "-");
//    printf( (File_Stat.st_mode & S_IXUSR) ? "x" : "-");
//    printf( (File_Stat.st_mode & S_IRGRP) ? "r" : "-");
//    printf( (File_Stat.st_mode & S_IWGRP) ? "w" : "-");
//    printf( (File_Stat.st_mode & S_IXGRP) ? "x" : "-");
//    printf( (File_Stat.st_mode & S_IROTH) ? "r" : "-");
//    printf( (File_Stat.st_mode & S_IWOTH) ? "w" : "-");
//    printf( (File_Stat.st_mode & S_IXOTH) ? "x" : "-"); 
//    printf(" ");
//    printf("%d ",File_Stat.st_nlink);
//    pw=getpwuid(File_Stat.st_uid);
//    printf("%s ",pw->pw_name);
//    gp=getgrgid(File_Stat.st_gid);
//    printf("%s ",gp->gr_name);
//    printf("%4d ",File_Stat.st_size);
//    c=ctime(&File_Stat.st_mtime);
//    for(i=4;i<=15;i++)
//      printf("%c",c[i]);
//    printf(" ");
//    printf("%s\n",myfile->d_name);
//  }
//  closedir(mydir);  
//  return 0;
//
//}
//	/* see man page for opendir() and readdir() and print out filenames for
//	the directory passed */
// /* list() */
//