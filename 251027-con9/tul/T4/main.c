#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>

/*
implement following command
prog < f1 >> f2 2> f3
*/

int 
main(int argc, char **argv)
{
    int f1 = open(argv[2], O_RDONLY);
    dup2(f1, STDIN_FILENO);
    close(f1);

    int f2 = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 0666);
    dup2(f2, STDOUT_FILENO);
    close(f2);

    int f3 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
    dup2(f3, STDERR_FILENO);
    close(f3);

    execlp(argv[1], argv[1], NULL);
    exit(1);
}