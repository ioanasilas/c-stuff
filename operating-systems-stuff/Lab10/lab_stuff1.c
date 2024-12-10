#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


//Parent sends son sigusr signal every second

float a = 0, r = 1;
int counter = 0;

void handler(int sig)
{
  a = a + (1/r);
  printf("GOT SIGUSR1 %f\n", a);
  counter++;
  if (counter == 2)
  {
    exit(42);
  }
}

int main(int argc, char **argv)
// convert argv converted to float
// get status of kid process

{ 
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <a0> <r>\n", argv[0]);
    exit(1);
  }

  // parse cmd args
  a = atof(argv[1]);
  r = atof(argv[2]);

  if (r == 0)
  {
    fprintf(stderr, "Error: r must be different from 0\n");
    exit(1);
  }

  // both parent and kid are not allowing this issue
  signal(SIGUSR1, SIG_IGN);

  int id = fork();
  if (id < 0)
  {
    fprintf(stderr, "Error creating process\n");
    exit(2);
  }
  
  // kid process
  if (id == 0)
  {
        if (signal(SIGUSR1, handler) == SIG_ERR)
    {
      fprintf(stderr, "Error handling SIGINT in kid\n");
      exit(3);

    }
    // forever wait
    while(1);
  }

  // parent
  printf("*****");
  for(int i = 0; ; i++)
  {
    // wait 1 second, send SIGUSR1 to kid
    sleep(1);
    kill(id, SIGUSR1);
    if(i % 2)
      printf("+++++\n");
    else
      printf("-----\n");

    // add status to check if kid exited normally
    int status;
    pid_t result = waitpid(id, &status, WNOHANG);
    // kid process exited
    if (result > 0)
    {
      // check if kid exited normally
      if (WIFEXITED(status))
      {
        printf("Kid exited with code: %d\n", WEXITSTATUS(status));
      }
    }
  }
  return 0;
}