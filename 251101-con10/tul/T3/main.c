/*
(pr1; pr2) | pr3 > file
left part if unique process
*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <sys/file.h>

int
main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        pid_t pid = fork();
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        if (pid == 0) {
            // close(fd[0]), close(fd[1]);
            execlp(argv[1], argv[1], NULL);
        }

        wait(NULL);

        pid = fork();
        if (pid == 0) {
            // dup2(fd[1], STDOUT_FILENO);
            execlp(argv[2], argv[2], NULL);
        }

        wait(NULL);
        return 0;
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        int f = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(f, STDOUT_FILENO);
        close(f);

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]), close(fd[1]);

        execlp(argv[3], argv[3], NULL);
    }

    close(fd[0]), close(fd[1]);
    while (wait(NULL) != -1);
    return 0;
}
