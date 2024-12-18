#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Afficher le prompt
    printf("$ ");

    // Lire la ligne de l'utilisateur avec getline
    read = getline(&line, &len, stdin);
    
    // Vérifier la fin de fichier (EOF) ou erreur de lecture
    if (read == -1) {
        if (feof(stdin)) {
            // Si EOF, afficher un message et quitter
            printf("\nEnd of file (EOF) reached. Exiting...\n");
        } else {
            // Si erreur lors de la lecture
            perror("getline");
        }
        free(line);
        return 1;  // Quitter avec un code d'erreur
    }

    // Supprimer le caractère de nouvelle ligne (\n) à la fin de la ligne
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    // Afficher la ligne entrée
    printf("%s\n", line);

    // Libérer la mémoire allouée par getline
    free(line);
    
    return 0;
}
