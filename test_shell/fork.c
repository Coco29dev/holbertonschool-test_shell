#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Création d'un processus fils

    if (pid == -1) {
        // Erreur lors de la création du processus
        perror("fork échoué");
        return 1;
    } else if (pid == 0) {
        // Code exécuté par le processus fils
        printf("Je suis le processus fils, mon PID est %d\n", getpid());
    } else {
        // Code exécuté par le processus parent
        printf("Je suis le processus parent, le PID du fils est %d\n", pid);
    }

    return 0;
}
