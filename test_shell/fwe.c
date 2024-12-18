#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;

    // Création de 5 processus enfants
    for (i = 0; i < 5; i++) {
        pid = fork();  // Crée un processus enfant
        
        if (pid < 0) {
            // En cas d'erreur
            perror("fork échoué");
            exit(1);
        } else if (pid == 0) {
            // Dans le processus enfant
            printf("Enfant %d: Exécution de 'ls -l /tmp'\n", i + 1);

            // Exécution de la commande 'ls -l /tmp'
            execlp("ls", "ls", "-l", "/tmp", (char *)NULL);
            
            // Si execlp échoue
            perror("Erreur de execlp");
            exit(1);
        } else {
            // Dans le processus parent
            // Attendre que l'enfant termine avant de créer un nouveau processus
            wait(NULL);
        }
    }

    printf("Tous les processus enfants ont terminé.\n");
    return 0;
}
