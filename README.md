# Programming-Assignment-2
## Writing a Shell
### Objectives
The objectives of this project are to learn how a Unix shell works, to write a simple shell, to create processes, to handle signals, to use Unix system calls and C library function calls, and to become a better programmer. 
### Background readings
* Wikipedia articles on Unix shells and tcsh.
* Man pages for Unix system calls and C library function calls.
* Official tcsh man page.
* Shell skeleton code to get you started.
* Try Sample code to experiment more.
* Try a simple shell with one built-in command.
### The Assignment
You will write a simple shell in C with some "built-in" commands. 
#### Overview
What you need to do is to have a loop that will print a prompt (consisting of a "prefix," which is initially a blank (space), followed by ' [cwd]> ', where cwd is the "current working directory," and will execute commands until the exit command is entered. In the loop you should check if the command is one of your built-in commands (given later) or a program in the search paths. You also need to support passing arguments to the commands (i.e., you will need to build an argv array). If the command entered is neither one of your built-in commands nor in the search paths, you should print "command: Command not found." where command is the command name that was entered.
#### More Details
* Obviously, you will need to do some parsing of the command line entered. A good way to do this would be to use fgets(3) to read in the (entire) command line, then use strtok(3) with a space as the delimiter. The first "word" will be the command (where we'll ignore the possibility that a command could have a space in its name). All words after that will be arguments to be passed to the command (which you will need to put into a char**).
* After you get the command, check if it is one of your built-in commands (explained below). If it is, then call the function for that.
* If it is not one of your built-in commands, check if it is an absolute path (a command starts with '/') or a path starts with './', '../', etc., and run that if it is executable (use access(2) to check).
* If the command is neither of the above cases then search for the command in the search path by looping through the path stored as a linked list as given in the skeleton code. You may also use your own linked list code. Use access(2) in a loop to find the first executable in the path for the command. snprintf(3) would be useful to use here (as using strcat() has caused problems for several people).
* Once you find the command you should execute it, using execve(2). You also need to have the shell do a waitpid(2) and print out the return status of the command if it is nonzero like tcsh does when the printexitvalue shell variable is set. Look into using the WEXITSTATUS macro from <sys/wait.h>.
* Before executing a command your shell should also print out what it is about to execute. (i.e. print "Executing [pathname]"; for built-ins print "Executing built-in [built-in command name]")
* Ctrl-C (SIGINT) should be caught and ignored if the shell is prompting for a command, but sent to the running child process otherwise. Use signal(2) and/or sigset(3) for this. Ctrl-Z (SIGTSTP), and SIGTERM should be ignored using sigignore(3) or signal(3). Note that when you are running a command inside your shell and press control-C, signal SIGINT is sent to both your shell process and the running command process (i.e., all the processes in the foreground process group). (Review Sections 9.4 (Process Groups), 9.5 (Sessions), and 9.6 (Controlling Terminal) of Stevens and Rago's APUE book for details.)
* You need to support the * wildcard character when a single * is given. You do not need to handle the situation when * is given with a / in the string (i.e., /usr/include/*.h). This should work just like it does in csh/tcsh when noglob is not set. You need only to support the possibility of one * on your commandline, but it could have characters prepended and/or appended. (That is, ls * should work correctly as should ls *.c, ls s*, ls p*.txt, etc.) Be sure to document how you do this. Hint: implement the list built-in command explained below before attempting this. You may use glob(3) or wordexp(3)if you wish. [Review glob.c in sample code] Note that it is YOUR shell's responsibility to expands wildcards to matching (file) names. (See an example here.) If there were no matches, the "original" arguments are passed to execve(). You would only need to make the wildcard to work with external commands.
* You also need to support the ? wildcard character which should match any single character (exactly one character match) in a filename (anywhere in the filename). The * and ? should also work together.
* Your code should do proper error checking. Again check man pages for error conditions, and call perror(3) as needed. Also avoid memory leaks by calling free(3) as needed.
* Your shell should treat Ctrl-D and the EOF char in a similar way csh/tcsh do when the ignoreeof tcsh shell variable is set, i.e., ignore it, instead of exiting or seg faulting. Note that Ctrl-D is not a signal, but the EOF char. (Please review the difference between Shell Variables and Environment Variables.)
#### Built-in Commands to support
* exit - obvious!
* which - same as the tcsh one (hint: you can write a function to do this and use it for finding the command to execute) [Review get_path_main.c in shell skeleton code for details]
* where - same as the tcsh one (reports all known instances of command in path) [Review get_path_main.c in shell skeleton code]
* cd - chdir(2) to directory given; with no arguments, chdir to the home directory, with a '-' as the only argument, chdirs to directory previously in, the same as tcsh does. [Review Stevens and Rago's Section 4.23 for details]
* pwd - print the current working directory. [Review getcwd.c in sample code; review Stevens and Rago's Section 4.23 for details]
* list - with no arguments, lists the files in the current working directory one per line. With arguments, lists the files in each directory given as an argument, with a blank line then the name of the directory followed by a : before the list of files in that directory. You will need to use opendir(3) and readdir(3). (Hint: read their respective man pages carefully, and refer to Fig. 1.3 of Stevens and Rago's APUE book)
* pid - prints the pid of the shell
* kill - When given just a pid sends a SIGTERM to it with kill(2). When given a signal number (with a - in front of it) sends that signal to the pid. (e.g., kill 5678, kill -9 5678).
* prompt - When ran with no arguments, prompts for a new prompt prefix string. When given an argument make that the new prompt prefix. For instance, let's assume cwd is /usa/cshen.
```
 [/usa/cshen]> prompt CISC361
CISC361 [/usa/cshen]> _
CISC361 [/usa/cshen]> cd 361
CISC361 [/usa/cshen/361]> prompt YES
YES [/usa/cshen/361]> prompt
  input prompt prefix: hello
hello [/usa/cshen/361]> _
```
* printenv - Should work the same as the tcsh built-in one. When ran with no arguments, prints the whole environment. (This can be done in 2 lines of code, a printf() inside of a while loop, not counting a variable declaration). When ran with one argument, call getenv(3) on it. When called with two or more args print the same error message to stderr that tcsh does. (Review Stevens and Rago's Section 7.5 Environment List [and Section 7.4 Command-Line Arguments] for details.)
* setenv - Should work the same as the tcsh built-in one. When ran with no arguments, prints the whole environment, the same as printenv. When ran with one argument, sets that as an empty environment variable. When ran with two arguments, the second one is the value of the first. When ran with more args, print the same error message to stderr that tcsh does. You can use the setenv(3) function for this command. Special care must be given when PATH and HOME are changed. When PATH is changed, be sure to update your linked list for the path directories (and free() up the old one). When HOME is changed cd with no arguments should now go to the new home. Provide your own test runs to show this works. (Review Stevens and Rago's Section 7.9 Environment Variables for details.)
#### How to get started
It is recommendated to first get the loop working to find a command, i.e., implement which first. Then you will be able to create a new process with fork(2) and use execve(2) in the child process and waitpid(2) in the parent. Then process arguments and do the other built-ins. Remember to read man pages for system and library calls, include the corresponding header files. 

Skeleton code to get started with is here. Example code of using fork(2) and exec(2) can be found here. 
#### Some more library functions that may be helpful
atoi(3), fprintf(3), index(3), calloc(3), malloc(3), memcpy(3), memset(3), getcwd(3), strncmp(3), strlen(3).
#### About which and where
The best way to learn the ideas of these two commands is to use the following code (that are part of the Shell skeleton code) to create an executable as follows. 

get_path.c get_path.h	get_path_main.c 

$ gcc get_path.c get_path_main.c 
$ ./a.out 

In tcsh, you can add a directory called /usr/local/bin to the END of search path by entering the following command and then print the new value. 
$ cset path = ($path /usr/local/bin) 
$ echo $path 

If you want to add the directory to the FRONT of search path, do 
$ set path = (/usr/local/bin $path) 

In bash, do 
$ PATH=$PATH:/usr/local/bin 
$ export PATH 

To add to the FRONT of path, do 
$ PATH=/usr/local/bin:$PATH 

Both which and where will start searching for the target from the front of the path/PATH value.
### Test Runs
Test your shell by running the following commands in it (in order):
```
[return]
Ctrl-D
Ctrl-Z
Cotrl-C
which					; test which
which ls
ls					; execute it
[return]
Ctrl-D					; make sure still work
Ctrl-Z
Ctrl-C
ls -l					; test passing arguments
ls -l -a /proc/tty
ls -l -F /proc/tty
ls -l -F /etc/perl
ls -l -a /etc/perl
where					; test where
where ls
/bin/ls -l -g			; test absolutes and passing args
/bin/ls -l
file *					; test out * wildcard
ls *
ls *.c
ls -l sh.*
ls -l s*.c
ls -l s*h.c
ls sh.?					; test out ? wildcard
ls ?h.c	
ls *.?					; test combination of ? and *	
blah					; try a command that doesn't exist
/blah					; an absolute path that doesn't exist
ls -l /blah
/usr/bin				; try to execute a directory
/bin/ls -la /
file /bin/ls /bin/rm
which ls rm				; test multiple args
where ls rm
list					; test list
list / /usr/proc/bin
cd 					; cd to home
pwd
cd /blah				; non-existant
cd /usr/bin /usr/ucb			; too many args
cd -					; should go back to project dir
pwd
more sh.c   (and give a Crtl-C)		; more should exit
cd /usr/bin
pwd
./ls /					; test more absolutes
../bin/ls /
pid					; get pid for later use
kill
kill pid-of-shell			; test default
kill -1 pid-of-shell			; test sending a signal, should kill
					; the shell, so restart a new one
prompt	    (and enter some prompt prefix)
prompt 361shell
printenv PATH
printenv
setenv
setenv TEST
printenv TEST
setenv TEST testing
printenv TEST
setenv TEST testing more
setenv HOME /
cd
pwd
exit
```
### Notes
The next project builds upon this project. It is important to have minimal functionality of this project in order to complete the next project.
### Extra Credits
Turn your shell into one that will restrict the execution time of a running command (process). Your shell will execute a command as a new process, but if the process exceeds a 'timeout' value in seconds, it will be killed. You will start your shell with one argument stating the timeout value (in seconds). For instance,
```
$ ./myshell 5
mysh >>
mysh >> cat
!!! taking too long to execute this command !!!
mysh >>
mysh >>
```
You may NOT use multi-threading to implement this feature.
