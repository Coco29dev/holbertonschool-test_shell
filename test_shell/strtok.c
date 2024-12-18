#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Bonjour, comment ça va ?";
    char *token = strtok(str, " ,?");
    int count = 1;
    while (token != NULL) {
        printf("Argument %d : %s\n",count, token);
        token = strtok(NULL, " ,?");
	count++;
    }

    return 0;
}
