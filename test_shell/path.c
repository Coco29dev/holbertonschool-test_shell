#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * print_path - Affiche chaque répertoire contenu dans la variable PATH.
 */
void print_path(void)
{
    char *path = getenv("PATH");
    if (path != NULL)
    {
        char *dir = strtok(path, ":");
        while (dir != NULL)
        {
            printf("%s\n", dir);
            dir = strtok(NULL, ":");
        }
    }
    else
    {
        printf("PATH n'est pas défini.\n");
    }
}

/**
 * main - Teste print_path.
 *
 * Return: Toujours 0.
 */
int main(void)
{
    print_path();
    return 0;
}
