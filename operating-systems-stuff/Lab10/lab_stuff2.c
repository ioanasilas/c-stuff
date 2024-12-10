#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int running = 1; // to control the parent loop

// handler for SIGUSR1 to terminate the parent process
void handle_sigusr1(int sig)
{
    running = 0;
    printf("Received SIGUSR1 => terminating parent process.\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);
    if (N <= 0)
    {
        fprintf(stderr, "N must be a positive int.\n");
        exit(1);
    }

    signal(SIGUSR1, handle_sigusr1); // set up SIGUSR1 handler for the parent

    // first child process

    // we do not need signal handling for kids
    // since the switching is managed by the parent using
    // SIGSTOP snd SIGCONT and these cannot be caught, blocked or ignored
    // they are caught by the os

    pid_t child1 = fork();
    if (child1 < 0)
    {
        perror("Error creating first child");
        exit(1);
    }

    if (child1 == 0)
    {
        // first child process
        while (1)
        {
            printf("Process 1 is running...\n");
            sleep(1);
        }
        exit(0); // exit if the loop ends
    }

    //second child process
    pid_t child2 = fork();
    if (child2 < 0)
    {
        perror("Error creating second child");
        exit(1);
    }

    if (child2 == 0)
    {
        // second child process
        while (1)
        {
            printf("Process 2 is running...\n");
            sleep(1);
        }
        exit(0); // exit if the loop ends
    }

    // parent process
    // we stop it using the PID from the terminal
    // by doing kill -SIGUSR1 <pid>
    printf("Parent process started. PID: %d\n", getpid());

    // allow the first child to run first
    kill(child2, SIGSTOP); // stop the second child
    printf("Process 2 was put on hold -- Process 1 running.\n");

    while (running)
    {
        sleep(N);

        // switch to 2nd process
        kill(child1, SIGSTOP); // stop 1st kid
        kill(child2, SIGCONT); // continue 2nd kid
        printf("Process 1 was put on hold -- Process 2 started.\n");

        sleep(N);

        // switch to 1st process
        kill(child2, SIGSTOP); // Stop 2nd kid
        kill(child1, SIGCONT); // continue 1st kid
        printf("Process 2 was put on hold -- Process 1 started.\n");

        // force a break when SIGUSR is received
        // why is this necessary?
        if (!running)
        {
          break;
        }
    }

    // terminate both children, wait for them to finish
    kill(child1, SIGTERM);
    kill(child2, SIGTERM);
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    printf("Parent process terminated.\n");
    return 0;
}
