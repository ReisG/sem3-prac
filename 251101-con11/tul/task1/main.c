#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static volatile int cnt = 0;
void handler(int sig)
{
    cnt++;
    if (cnt == 4) signal(SIGINT, SIG_DFL);
}

int 
main(void)
{
    signal(SIGINT, handler);
    for (;;) pause();
}