#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Mon PID est : %d\n", getpid());
	printf("PID du processus parent : %d\n", getppid());
return (0);
}
