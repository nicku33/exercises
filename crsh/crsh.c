#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/**
* prints out the command line prompt
* returns a char array where the first element is the exectuable command and the second is the rest of the args
**/
int parseInput(char inBuff[], char ** cmd, char ** args) {

  // STDIN_FILENO?
  // parse it
  *cmd = strtok(inBuff, " ");
  *args = strtok(NULL, "");\
  return 0;
}

int main (int argc, char** argv){

    int n;
    int BUF_MAX=1024;
    pid_t cpid;
    pid_t pid = getpid();
    char b[BUF_MAX];
    char * cmd;
    char * args;
    //
    // get the parent process id
    printf("\n-------\n");
    printf("Parent pid = %d\n", pid);

    int count = 0;
    while (++count <= 10) {
        sleep(1);
        printf ("\nLoop %d\n", count);
//        printf ("$");

        // print the prompt
        printf("$> ");
        // read line
        scanf("%1024[^\n]", b);
        // read line
        // STDIN_FILENO
        // parse it
        parseInput(b, &cmd, &args);

        printf("the command is... %s\n", cmd);

        // if it's EXIT exit
        cpid = fork();
        printf ("got %d from fork()\n", cpid);

        // can cpid return an error condition ?
        if (cpid < 0){
            printf("Failed to fork !!\n");
            exit(1);
        }

        int stat_loc = -1;
        if (cpid != 0){
            printf("Parent pid %d waiting for child %d ...\n", pid, cpid);
            sleep(1);
            waitpid(cpid, &stat_loc, 0);
            printf("Child process exited with exit code %d.\n", stat_loc);
        } else {
            char* argv[2];
            argv[0]="wa";
            argv[1]=NULL;
            printf("Child pid %d executing %s\n", cpid, path);
            sleep(1);
            int error = execv(path, argv);
            printf("I should never reach here %d, got errorcode %d\n", error, errno);
            exit(0);
        }
    }
    return 0;

}
