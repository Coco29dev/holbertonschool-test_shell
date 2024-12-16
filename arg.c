#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	for (char **arg = av; *arg != NULL; arg++)
{
	printf("%s\n", *arg);
}
return (0);
}
