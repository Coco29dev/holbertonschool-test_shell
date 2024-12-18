#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    // Parcourir les arguments passés au programme et les afficher
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        i++;
    }

    return 0;
}
