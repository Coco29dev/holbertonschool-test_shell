#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int i;

    // Création de 5 processus enfants
    for (i = 0; i < 5; i++) {
        pid = fork();  // Création d'un processus enfant
        
        if (pid == -1) {
            // Si fork échoue
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) {
            // Code exécuté par le processus enfant
            char *argv[] = { "ls", "-l", "/tmp", NULL };  // Commande à exécuter
            char *envp[] = { NULL };  // Environnement (utiliser l'environnement par défaut)
            
            // Exécution de la commande dans l'enfant
            execve("/bin/ls", argv, envp);
            
            // Si execve échoue
            perror("execve failed");
            exit(EXIT_FAILURE);
        } else {
            // Code exécuté par le père
            wait(NULL);  // Le père attend que l'enfant termine
        }
    }

    printf("Tous les enfants ont terminé.\n");
    return 0;
}
