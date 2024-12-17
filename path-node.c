#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
// Définition du nœud de la liste chaînée
typedef struct Node {
    char *directory;  // Répertoire contenu dans le PATH
    struct Node *next;  // Pointeur vers le nœud suivant
} Node;

// Fonction qui crée un nouveau nœud de liste chaînée
Node *create_node(char *directory)
{
    Node *new_node = malloc(sizeof(Node));  // Allouer de la mémoire pour un nouveau nœud
    if (new_node == NULL)
    {
        perror("Erreur d'allocation de mémoire");
        exit(1);  // Quitter si l'allocation échoue
    }

    new_node->directory = strdup(directory);  // Allouer une copie de la chaîne de caractères
    new_node->next = NULL;  // Initialiser le pointeur suivant à NULL
    return new_node;
}

// Fonction qui construit la liste chaînée des répertoires dans PATH
Node *build_path_list(void)
{
    char *path = NULL;
    char *directory = NULL;
    Node *head = NULL;  // Tête de la liste chaînée
    Node *current = NULL;  // Pointeur pour parcourir la liste chaînée

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
        return NULL;
    }

    // Séparer le PATH en répertoires individuels en utilisant strtok
    directory = strtok(path, ":");

    // Construire la liste chaînée
    while (directory != NULL)
    {
        Node *new_node = create_node(directory);  // Créer un nouveau nœud
        if (head == NULL)  // Si la liste est vide, le premier nœud devient la tête
        {
            head = new_node;
            current = head;
        }
        else  // Sinon, ajouter le nœud à la fin de la liste
        {
            current->next = new_node;
            current = new_node;
        }
        directory = strtok(NULL, ":");  // Continuer à découper la chaîne
    }

    return head;  // Retourner la tête de la liste chaînée
}

// Fonction qui affiche la liste chaînée
void print_path_list(Node *head)
{
    Node *current = head;

    while (current != NULL)
    {
        printf("%s\n", current->directory);
        current = current->next;
    }
}

// Fonction pour libérer la mémoire allouée à la liste chaînée
void free_path_list(Node *head)
{
    Node *current = head;
    Node *next_node;

    while (current != NULL)
    {
        next_node = current->next;
        free(current->directory);  // Libérer la chaîne de caractères
        free(current);  // Libérer le nœud
        current = next_node;
    }
}

int main(void)
{
    // Construire la liste chaînée des répertoires dans PATH
    Node *head = build_path_list();

    // Afficher la liste chaînée
    if (head != NULL)
    {
        print_path_list(head);
    }

    // Libérer la mémoire allouée
    free_path_list(head);

    return 0;
}
