#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CMD_LEN 1024

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    
    // Boucle principale du shell
    while (1)
    {
        // Affiche le prompt
        printf("#cisfun$ ");
        
        // Lit la ligne de commande
        read = getline(&line, &len, stdin);
        if (read == -1)  // Si la lecture échoue (CTRL+D ou erreur)
        {
            perror("getline");
            break;
        }

        // Supprime le caractère de nouvelle ligne à la fin de la commande
        line[read - 1] = '\0';

        // Si l'utilisateur entre une commande vide, continue
        if (strlen(line) == 0)
            continue;

        // Crée un processus enfant
        pid = fork();

        if (pid == -1)  // Si fork échoue
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            // Dans le processus enfant, exécute la commande avec execve
            char *argv[] = {line, NULL};  // La commande entrée est le premier argument
            if (execve(line, argv, NULL) == -1)
            {
                // Si execve échoue
                perror("Error");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Dans le processus parent, attend que l'enfant termine
            wait(NULL);
        }
    }

    // Libère la mémoire allouée pour la ligne
    free(line);
    return 0;
}
