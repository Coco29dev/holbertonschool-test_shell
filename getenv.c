#include <stdio.h>
#include <string.h>

extern char **environ;  // Déclaration de la variable globale environ

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable to search for.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
    char **env = environ;  // Déclaration d'un pointeur pour parcourir environ
    size_t name_len = strlen(name);  // Longueur du nom de la variable d'environnement

    // Parcours du tableau environ
    while (*env != NULL)
    {
        // Comparer les premiers caractères jusqu'au signe '='
        if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
        {
            // Retourner la partie après le signe '=' (valeur de la variable)
            return *env + name_len + 1;  // On saute le nom et le '='
        }
        env++;  // Passer à la variable d'environnement suivante
    }

    return NULL;  // Retourner NULL si la variable n'a pas été trouvée
}

int main(void)
{
    // Exemple d'utilisation de _getenv
    char *value = _getenv("HOME");  // Récupérer la variable HOME
    if (value)
    {
        printf("HOME=%s\n", value);
    }
    else
    {
        printf("HOME not found\n");
    }

    return 0;
}
