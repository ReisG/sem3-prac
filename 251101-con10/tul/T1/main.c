/*
pr1 | pr2
*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <errno.h>
#include <string.h>

#include <sys/wait.h>

int
main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "wrong args\n");
        exit(1);
    }

    int fd[2];
    if (pipe(fd) < 0)
    {
        fprintf(stderr, "cannot create pipe\n");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        // child
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        exit(1); // 
    }
    
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        // child
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[2], argv[2], NULL);
        exit(1); // 
    }

    close(fd[0]);
    close(fd[1]);
    while (wait(NULL) != -1);

    return 0;

}
