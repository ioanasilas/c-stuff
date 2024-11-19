#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUFFER_SIZE 2000

// pipe1: parent-to-child communication
// pipe2: child-to-parent communication

// Parent Process reads the file content and reverses it using reverse_string,
//                sends the reversed content to the child process via a pipe.

// Child Process receives the reversed content from the parent,
//               processes the content to count digits, uppercase, lowercase characters, and others,
//               sends back a formatted response to the parent.


// reverse string
void reverse_string(char *str, int length) {
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

int main(int argc, char *argv[]) 
{
    // variables to be able to format data
    int nr_digits = 0;
    char digits[BUFFER_SIZE] = {0};

    int nr_uppercase = 0;
    char uppercase[BUFFER_SIZE] = {0};

    int nr_lowercase = 0;
    char lowercase[BUFFER_SIZE] = {0};

    int nr_others = 0;
    char others[BUFFER_SIZE] = {0};

    // to wait for child
    int status;

    // take argvs, first is exe, second is path
    if (argc != 2) {
        fprintf(stderr, "How to use: %s <file_path>\n", argv[0]);
        exit(-1);
    }

    char *file_path = argv[1];

    // open actual file
    FILE *file = fopen(file_path, "r");
    // andle error
    if (!file) 
    {
        perror("Error opening file");
        exit(-1);
    }

    // read in buffer, then close the file
    char buffer[BUFFER_SIZE];
    int bytes_read = fread(buffer, 1, BUFFER_SIZE - 1, file);
    fclose(file);

    if (bytes_read == 0) 
    {
        fprintf(stderr, "File is empty or we cannot read.\n");
        exit(-1);
    }
    // null terminate string
    // for strlen printf etc
    buffer[bytes_read] = '\0';

    // do reverse of the content read
    reverse_string(buffer, bytes_read);

    // create the pipes that assigns 2 file descriptors as positive integers
    // so we compare to -1 to check for failure
    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) 
    {
        perror("Pipe creation was not successful");
        exit(-1);
    }

    // we have the pipe, so we fork so both parent and kid process can access it
    int pid = fork();
    if (pid == -1) 
    {
        perror("Fork failed");
        exit(-1);
    }

    if (pid == 0) 
    { // child process
      // we close the unused ends from the 2 pipes
        close(pipe1[1]);
        close(pipe2[0]);

      // read what was sent by parent from pipe1,
      // store it in received
        char received[BUFFER_SIZE];
        read(pipe1[0], received, BUFFER_SIZE);
        close(pipe1[0]);

        // handle read data by seeing how many nos, digits etc we have and
        // save in corresponding arrays
        char processed[BUFFER_SIZE];
        for (int i = 0; i < strlen(received); i++) 
        {
            if (isdigit(received[i])) 
            {
                digits[nr_digits++] = received[i];
            } 
            else if (isupper(received[i])) 
            {
                uppercase[nr_uppercase++] = received[i];
            } 
            else if (islower(received[i])) 
            {
                lowercase[nr_lowercase++] = received[i];
            } 
            else 
            {
                others[nr_others++] = received[i];
            }
        }

    // format output, store in buffer
    sprintf(processed, "%d%s%d%s%d%s%d%s", nr_digits, digits, nr_uppercase, uppercase, nr_lowercase, lowercase, nr_others, others);

        // write back to parent, close write end after
        write(pipe2[1], processed, strlen(processed));
        close(pipe2[1]);

        exit(0);
    } 
    else 
    { // parent process based on PID
      // we close unused ends, read from pipe1 and write from pipe2
        close(pipe1[0]);
        close(pipe2[1]);

        // write content to child, then close write end
        write(pipe1[1], buffer, bytes_read);
        close(pipe1[1]);

        // get response from child with info, close read end
        char response[BUFFER_SIZE];
        read(pipe2[0], response, BUFFER_SIZE);
        close(pipe2[0]);

        printf("Processed content from child: %s\n", response);
        wait(&status); // wait for child , avoid deadlock
    }

    return 0;
}
