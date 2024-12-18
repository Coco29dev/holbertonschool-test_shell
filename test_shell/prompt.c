#include "shell.h"


int main (void)
{
	char *line = NULL; // Pointeur ers la ligne lue
	size_t len = 0; // Taille allouee pour la ligne
	ssize_t read; // Nombre de caracteres lus

// boucle infinie pour repeter l'invite
	while (1)
{
	// afficher l'invite
	printf("$ ");

	// Lire la ligne depuis stdin (le clavier)
	read = getline(&line, &len, stdin);

	// si nous rencontrons EOF (ctrl+D), on sort de la boucle
	if (read == -1)
{

	// si c'est EOF (fin de fichier), on quitte le programme
	if (feof(stdin))
{
 	printf("\n");
	break; // quitter la boucle si EOF est rencontre
}

	// si une autre erreur se produit
	else
{
	perror("getline");
	break; // quitter en cas d'erreur
}
}

// afficher la commande lue
printf("%s", line);
}

// liberer la memoire allouee pour la ligne
free(line);
return (0);
}
