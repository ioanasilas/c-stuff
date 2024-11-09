#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/*
The whiteboard scheme was the following:
- the user provides the number of iterations as a command line argument
- there should be just one parent process creating one kid process per iteration
- the child should not create its own process, but rather exit after being created
- so we have just one parent process, the same, creating a different child each iteration
- also, we print to see if the current iteration is even or odd
- each child process prints its pid and its parent's pid (which will always be the same)
- parent prints its own pid
*/


int main(int argc, char** argv) {
  int number_of_iterations = 0;
  if (argc > 1)
  {
    char * number_of_iterations_first = argv[1];
    for(int i = 0; i < strlen(number_of_iterations_first); i++)
    {
      if(number_of_iterations_first[i] < '0' || number_of_iterations_first[i] > '9')
      {
        fprintf(stderr, "That is not a valid number.\n");
        return 1;
      }
      number_of_iterations = number_of_iterations * 10 + (number_of_iterations_first[i] - '0');
    }
    printf("%d\n", number_of_iterations);
  }
  else
  {
    fprintf(stderr, "No number provided as command line argument.\n");
    return 5;
  }
  
  for(int i = 0; i < number_of_iterations; i++)
  {
    int status;
    if (i % 2 == 1)
    {
      printf("I'm an odd iteration, number %d!:D\n", i);
    }
    else
    {
      printf("I'm an even iteration, number %d!\n", i);
    }
    int pid = fork();
    if (pid < 0)
    {
      perror("Fork failed");
      exit(1);
    }
    else if (pid == 0)
    {
      printf("Hello from kid process with pid = %d, whose parent has pid = %d\n", getpid(), getppid());
      exit(0);
    }
    else if (pid > 0)
    {
      printf("Hello from parent process with pid = %d\n", getpid());
      wait(&status);     
    }
  }
  return 0;
}
