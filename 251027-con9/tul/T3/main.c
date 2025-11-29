#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

/*
Implement following shell command
(f1 || f2) && f3
input is in argv
*/

int
f(char *name)
{
    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "cannot fork(): %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // child
        execlp(name, name, NULL);
        fprintf(stderr, "cannot execlp in child: %s\n", strerror(errno));
        exit(1);
    }
    // father
    int status = 0;
    while (wait(&status) != -1) {
    }

    return WIFEXITED(status) && !WEXITSTATUS(status);
}

int
main(int argc, char **argv)
{
    return !( (f(argv[1]) || f(argv[2])) && f(argv[3]));
}
