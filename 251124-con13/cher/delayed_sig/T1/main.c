#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int flag = 0;

void
handler(int s)
{
    flag = 1;
}

int
main(void)
{
    sigaction(SIGINT, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);

    sigset_t s1, s2;
    sigemptyset(&s1);

    sigaddset(&s1, SIGINT);
    sigprocmask(SIG_BLOCK, &s1, &s2);
    while (1) {
        while (!flag) {
            sigsuspend(&s2);
        }
        printf("sigint\n");
        flag = 0;
    }
    // int c = getchar();
    // sleep(10);
    sigprocmask(SIG_UNBLOCK, &s1, NULL);
}
