#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    // in parr
    for (int i = 1; i < argc; ++i)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            // cannot run
            continue;
        }
        if (pid == 0)
        {
            // child
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }
    }

    int cnt = 0;
    int status = 0;
    while (wait(&status) != -1)
    {
        cnt += !WIFEXITED(status) || WEXITSTATUS(status);
    }
    printf("In parallel: %d\n", cnt);


    cnt = 0;
    for (int i = 1; i < argc; i++)
    {
        pid_t pid = fork();
        if (pid == -1) continue;
        if (pid == 0)
        {
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }

        int status = 0;
        waitpid(pid, &status, 0);
        cnt += !WIFEXITED(status) || WEXITSTATUS(status);
    }

    printf("On by one: %d\n", cnt);
    exit(1);
}