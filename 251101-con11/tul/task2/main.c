#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

static volatile long long sum = 0;
void wakeup(int sig)
{
    printf("%lld\n", sum);
    alarm(5);
}

int main(void)
{
    signal(SIGALRM, wakeup);
    alarm(5);

    int x = 0;
    while (scanf("%d", &x) == 1)
    {
        sum += x;
    }

    return 0;
}