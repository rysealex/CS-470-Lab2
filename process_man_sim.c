// Lab2 Process Management Simulator
// CS 470 - Operating Systems
// Alex Ryse

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// number of child processes to create
#define NUM_CHILD 10

// parent process starts from main
int main() {

    // display the parent the PID
    printf("Parent: PID = %d\n", getpid());

    // prepare arguments for execvp
    // inner arrays represent each command and its arguments, terminated by NULL pointer
    char* args[][10] = {
        {"ls", "-lia", NULL},
        {"echo", "Hello Alex", NULL},
        {"time", "ls", "-l", NULL},
        {"pwd", NULL},
        {"cat", "Makefile", NULL},
        {"ip", "a", NULL},
        {"who", NULL},
        {"date", NULL},
        {"ps", NULL},
        {"whoami", NULL},
    };

    int wpid; // process id of child that changed state, returned by waitpid()
    int status; // status info about terminated child

    // loop to create the child processes
    for (int i = 0; i < NUM_CHILD; i++) {
        pid_t pid = fork(); // creates a new child process

        if (pid < 0) {
            // error handling: fork failed if pid < 0
            perror("Fork failed");
            return 1;
        } else if (pid == 0) {
            /* executed by the child process only, pid == 0 means child */

            // display the current child's command
            printf("Child: PID = %d - Executing command: %s\n", getpid(),  args[i][0]);

            // execute the command using execvp
            if (execvp(args[i][0], args[i]) == -1) {
                // error handling: execvp failed if returned
                perror("execvp failed");
                return 1;
            }
            // should not be reached due to execvp replacing the child process and error handling
            return 0;
        }
    }

    /* executed by the parent process only, pid > 0 means parent */

    // parent process needs to wait for all children to complete
    for (int i = 0; i < NUM_CHILD; i++) {
        // wait for any child process to change state or terminate
        wpid = waitpid(-1, &status, 0);

        // checking if child process terminated normally
        if (WIFEXITED(status)) {
            printf("Child: PID = %d finished normally. Exit status = %d\n", wpid, status);
        } else {
            // display cases where child process terminates abnormally
            printf("Child: PID = %d finished abnormally.\n", wpid);
        }
    }

    // display that the parent process completed (end of program)
    printf("Parent Process Finished\n");

    return 0;
}