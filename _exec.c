#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
    // Ajouter une variable d'environnement temporaire
    setenv("MY_VAR", "HelloWorld", 1);

    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};  // Commande à exécuter

    printf("Before execve\n");

    // Appel à execve avec l'environnement actuel
    if (execve(argv[0], argv, environ) == -1)
    {
        perror("Error:");
    }

    printf("After execve\n");  // Ce code ne sera jamais exécuté si execve réussit
    return (0);
}
