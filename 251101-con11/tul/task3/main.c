#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

int fd[2];

void handl(int sig)
{
    pid_t pid_fr = 0;
    pid_t mypid = getpid();
    
    read(fd[0], &pid_fr, sizeof(pid_fr));
    int n = 0;
    read(fd[0], &n, sizeof(n));
    if (n >= 9)
    {
        kill(pid_fr, SIGTERM);
        kill(mypid, SIGTERM);
    }

    n++;
    write(fd[1], &mypid, sizeof(int));
    write(fd[1], &n, sizeof(n));

    printf("%d %d\n", mypid, n);
    kill(pid_fr, SIGUSR1);
}


int main(void)
{
    signal(SIGUSR1, handl);
    if (pipe(fd) < 0)
    {
        fprintf(stderr, "cannot pipe\n");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        while(1) pause();
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        while(1) pause();
        exit(0);
    }

    write(fd[1], &pid2, sizeof(pid2));
    int n = 0;
    write(fd[1], &n, sizeof(n));
    kill(pid1, SIGUSR1);

    //close(fd[0]);
    //close(fd[1]);

    while (wait(NULL) != -1);
    return 0;
}