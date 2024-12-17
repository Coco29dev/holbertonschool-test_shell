#include <stdio.h>
#include <stdlib.h>

extern char **environ;  // Déclaration de la variable globale environ

int main(void)
{
    // Parcourir toutes les variables d'environnement et les afficher
    for (char **env = environ; *env != NULL; env++)
    {
        printf("%s\n", *env);  // Affiche chaque variable d'environnement
    }

    return 0;
}
