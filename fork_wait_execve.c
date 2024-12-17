#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 5  // Nombre de processus enfants à créer

int main(void)
{
    pid_t pid;
    int i;

    // Création de 5 processus enfants
    for (i = 0; i < NUM_CHILDREN; i++)
    {
        pid = fork();  // Créer un processus enfant

        if (pid == -1)  // Si fork échoue
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)  // Code exécuté dans le processus enfant
        {
            // Arguments pour la commande ls -l /tmp
            char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
            
            // Remplacer le processus enfant par la commande ls
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("execve");  // Si execve échoue
                exit(EXIT_FAILURE);
            }
        }
        else  // Code exécuté dans le processus parent
        {
            // Le parent attend que l'enfant termine avant de créer un nouvel enfant
            wait(NULL);  // Attend la fin d'un enfant
        }
    }

    return 0;
}
