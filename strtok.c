#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "banana,orange,pataya,lemon,ananas";
    char *token = strtok(str, ",");  // Découpe la chaîne à chaque virgule

    while (token != NULL) {
        printf("phrase: %s\n", token);
        token = strtok(NULL, ",");  // Appels suivants, chaîne est déjà modifiée
    }

    return 0;
}
