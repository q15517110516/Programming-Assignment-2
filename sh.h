
#include "get_path.h"

int pid;
int sh( int argc, char **argv, char **envp);
char *which(char *command, struct pathelement *pathlist);
char *where(char *command, struct pathelement *pathlist);
void list ( char **args );
void printenv(char **envp);
char *cwd();
void mycd (char *cd,char **prePath,int *NumofPath);
#define PROMPTMAX 32
#define MAXARGS 10