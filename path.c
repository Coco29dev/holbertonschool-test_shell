#include <stdio.h>
#include <string.h>

extern char **environ;  // Déclaration de la variable globale environ

/**
 * print_path - Imprime chaque répertoire dans la variable d'environnement PATH.
 */
void print_path(void)
{
    char *path = NULL;
    char *directory = NULL;

    // Trouver la variable PATH dans environ
    for (char **env = environ; *env != NULL; env++)
    {
        if (strncmp(*env, "PATH=", 5) == 0)  // Si la variable commence par "PATH="
        {
            path = *env + 5;  // Sauter "PATH=" pour obtenir la chaîne des répertoires
            break;
        }
    }

    if (path == NULL)
    {
        printf("La variable d'environnement PATH n'a pas été trouvée.\n");
        return;
    }

    // Séparer le PATH en répertoires individuels en utilisant strtok
    directory = strtok(path, ":");

    // Afficher chaque répertoire sur une nouvelle ligne
    while (directory != NULL)
    {
        printf("%s\n", directory);
        directory = strtok(NULL, ":");  // Continuer à découper la chaîne
    }
}

int main(void)
{
    // Appeler la fonction pour imprimer le PATH
    print_path();
    return 0;
}
