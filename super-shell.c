#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CMD_LEN 1024

extern char **environ;  // To pass the environment to execve

// Function to handle user input and execute commands
int execute_command(char *cmd)
{
    pid_t pid;
    int status;

    // Create a child process
    pid = fork();

    if (pid == -1)  // Error in fork
    {
        perror("fork");
        return -1;
    }
    if (pid == 0)  // Child process
    {
        // Execute the command using execve
        if (execve(cmd, &cmd, environ) == -1)
        {
            perror("./shell");  // Print error if command cannot be executed
            exit(EXIT_FAILURE);
        }
    }
    else  // Parent process
    {
        // Wait for the child to finish executing
        wait(&status);
    }

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Main loop to read and execute commands
    while (1)
    {
        // Print the prompt
        printf("#cisfun$ ");

        // Read the command from standard input
        read = getline(&line, &len, stdin);
        if (read == -1)  // If EOF (Ctrl+D) or error in reading input
        {
            printf("\n");
            break;
        }

        // Remove the newline character at the end of the input
        line[read - 1] = '\0';

        // If the input is empty, continue to the next iteration
        if (strlen(line) == 0)
            continue;

        // Execute the command
        if (execute_command(line) == -1)
        {
            // Handle any errors in executing the command
            fprintf(stderr, "Error executing command: %s\n", line);
        }
    }

    // Free the memory allocated by getline
    free(line);

    return 0;
}
