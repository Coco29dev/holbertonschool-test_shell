#include "shell.h"

// Fonction principale du shell
int main(void) {
    char *command = NULL;  // Commande entrée par l'utilisateur
    size_t len = 0;  // Taille du buffer
    ssize_t nread;  // Nombre de caractères lus

    while (1) {
        print_prompt();  // Afficher le prompt

        nread = getline(&command, &len, stdin);  // Lire une ligne de commande
        if (nread == -1) {
            if (feof(stdin)) {  // Gérer EOF (Ctrl+D)
                printf("\n");
                free(command);
                exit(0);
            } else {
                perror("getline");
                exit(1);
            }
        }

        // Retirer le caractère de nouvelle ligne à la fin de la commande
        command[nread - 1] = '\0';

        // Si la commande est vide, on continue
        if (strlen(command) == 0) {
            continue;
        }

        // Exécuter la commande en utilisant exec.c
        execute_command(command);
    }

    free(command);
    return 0;
}
