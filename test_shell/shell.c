#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH 1024
#define DELIM " \t\r\n\a"

/**
 * split_input - Splits the input command into tokens
 * @input: The input command string
 * Return: Array of arguments (tokens)
 */
char **split_input(char *input)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "Shell: allocation error\n");
        exit(1);
    }

    token = strtok(input, DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "Shell: allocation error\n");
                exit(1);
            }
        }

        token = strtok(NULL, DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 * execute_command - Executes a command using execve in a child process
 * @command: The full path of the command to execute
 * @args: Arguments for the command
 */
void execute_command(char *command, char **args)
{
    pid_t pid = fork();

    if (pid == -1)  // Error in forking
    {
        perror("Fork failed");
        return;
    }

    if (pid == 0)  // Child process
    {
        if (execve(command, args, NULL) == -1)
        {
            perror("Error executing command");
        }
        exit(1);  // Exit child process if execve fails
    }
    else  // Parent process
    {
        int status;
        waitpid(pid, &status, 0);  // Wait for the child to finish
    }
}

/**
 * main - Main loop of the shell
 */
int main(void)
{
    char *input = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        // Afficher un prompt
        printf("#cisfun$ ");
        
        // Lire une ligne de commande
        nread = getline(&input, &len, stdin);
        if (nread == -1)  // Handle EOF or error
        {
            perror("getline");
            break;
        }

        // Enlever le '\n' de la commande
        input[nread - 1] = '\0';

        // Si la commande est vide, continuer à la boucle
        if (strlen(input) == 0)
        {
            continue;
        }

        // Séparer l'entrée en tokens
        char **args = split_input(input);

        // Exécuter la commande si elle n'est pas vide
        if (args[0] != NULL)
        {
            execute_command(args[0], args);
        }

        // Libérer la mémoire allouée
        free(args);
    }

    // Libérer la mémoire allouée pour l'entrée
    free(input);

    return 0;
}
