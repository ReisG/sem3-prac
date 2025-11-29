#include <unistd.h>
#include <stdio.h>

int
main(void)
{
	printf("%zu\n", sizeof(pid_t)); // int
	return 0;
}
