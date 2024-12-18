#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int i;

    for (i = 0; i < 5; i++) {
        pid = fork();  // Crée un enfant à chaque itération

        if (pid == 0) {
            // Code exécuté par le processus enfant
            printf("Enfant %d (PID: %d)\n", i + 1, getpid());
            sleep(i + 1);  // Chaque enfant attend un nombre de secondes différent
            exit(0);  // L'enfant termine ici
        }
    }

    // Code exécuté par le processus parent
    for (i = 0; i < 5; i++) {
        wait(NULL);  // Le parent attend tous ses enfants
        printf("Un enfant a terminé.\n");
    }

    return 0;
}
