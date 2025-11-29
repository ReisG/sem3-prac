#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

/*
ping-pong
push value between processes incrementing it
*/

void job(int n, int in, int out)
{
    while (1)
    {
        int val = 0;
        
        int res = read(in, &val, sizeof(val));
        if (res == 0) {
            return;
        }

        if (val > n) return;
        printf("%d %d\n", getpid(), val);
        val++;
        write(out, &val, sizeof(val));
    }
}

int
main(int argc, char **argv)
{
    char *end = NULL;
    int n = strtol(argv[1], &end, 10);

    int fd1[2];
    pipe(fd1);

    int fd2[2];
    pipe(fd2);

    int val = 1;
    write(fd1[1], &val, sizeof(val));

    pid_t pid1 = fork();
    if (pid1 == 0) {
        int in = dup(fd1[0]);
        int out = dup(fd2[1]);
        for (int i = 0; i < 2; i++) close(fd1[i]), close(fd2[i]);

        // first job
        job(n, in, out);
        close(in);
        close(out);

        return 0;
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        int in = dup(fd2[0]);
        int out = dup(fd1[1]);
        for (int i = 0; i < 2; i++) close(fd1[i]), close(fd2[i]);

        // second job
        job(n, in, out);

        close(in);
        close(out);

        return 0;
    }


    for (int i = 0; i < 2; i++) close(fd1[i]), close(fd2[i]);
    while (wait(NULL) != -1);
}