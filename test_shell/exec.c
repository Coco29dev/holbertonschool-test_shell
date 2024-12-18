#include "shell.h"

extern char **environ;  // Déclare environ pour passer l'environnement à execve()

// Fonction pour exécuter la commande
void execute_command(char *command) {
    pid_t pid = fork();  // Créer un nouveau processus

    if (pid == -1) {  // Erreur lors de la création du processus
        perror("fork");
        exit(1);
    }

    if (pid == 0) {  // Dans le processus fils
        // Si la commande est /bin/ls, exécuter avec les arguments "-l"
        if (strcmp(command, "ls") == 0) {
            char *argv[] = {"/bin/ls", "-l", NULL};  // Arguments pour "ls -l"
            if (execve(argv[0], argv, environ) == -1) {
                perror("./shell");
                exit(1);
            }
        } 
        // Si la commande est /bin/ls avec un chemin complet
        else if (strcmp(command, "/bin/ls") == 0) {
            char *argv[] = {"/bin/ls", "-l", NULL};  // Arguments pour "ls -l"
            if (execve(argv[0], argv, environ) == -1) {
                perror("./shell");
                exit(1);
            }
        } 
        // Sinon, essayer d'exécuter la commande directement
        else {
            if (execve(command, &command, environ) == -1) {
                perror("./shell");
                exit(1);
            }
        }
    } else {  // Dans le processus père
        wait(NULL);  // Attendre que le fils termine
    }
}



