#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

static volatile int int_flag = 0;
void
handler(int s)
{
    // it's forbidden to use
    // printf("sigint\n");

    // int e = errno;
    // static const char buf[] = "signal";
    // write(STDOUT_FILENO, buf, sizeof(buf) - 1);
    // errno = e;
    int_flag = 1;
}

int
main()
{
    // signal(SIGINT, handler);
    sigaction(SIGINT, &(struct sigaction) {.sa_flags = 0, .sa_handler = handler}, NULL);
    // sigaction(SIGFPE, &(struct sigaction) {.sa_flags = SA_RESTART, .sa_handler = handler}, NULL);
    signal(SIGFPE, SIG_IGN);

    // int x, y;

    // while (1) {
    //     errno = 0;
    //     int r = scanf("%d%d", &x, &y);
    //     if (r == EOF && errno == EINTR) {
    //         if (int_flag) {
    //             printf("signal\n");
    //             int_flag = 0;
    //         }
    //         continue;
    //     }
    //     if (r != 2) {
    //         break;
    //     }
    //     printf("%d\n", x / y);
    // }

    while (1) {
        while (!int_flag) {}
        printf("signal\n");
        int_flag = 0;
    }
    return 0;
}

// async-signal safe (ассинхронно безопасные функции) рентграбельные
//
