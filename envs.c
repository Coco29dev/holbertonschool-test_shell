#include <stdio.h>
#include <stdlib.h>

extern char **environ;  // Déclaration de la variable globale environ

int main(int argc, char *argv[], char *env[])
{
    // Afficher les adresses de env et environ
    printf("Adresse de 'env' : %p\n", (void *)env);
    printf("Adresse de 'environ' : %p\n", (void *)environ);

    // Vérifier si les adresses sont les mêmes
    if (env == environ)
    {
        printf("Les adresses de 'env' et 'environ' sont identiques.\n");
    }
    else
    {
        printf("Les adresses de 'env' et 'environ' sont différentes.\n");
    }

    return 0;
}
