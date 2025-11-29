#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>

int
main(void)
{
    execlp("ls", "ls", "-l", NULL);
    fprintf(stderr, "error: %s\n", strerror(errno));
    exit(1);
}
