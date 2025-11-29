#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/signalfd.h>

int
main(void)
{
    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGINT);
    sigaddset(&s1, SIGQUIT);

    int fd = signalfd(-1, &s1, SFD_CLOEXEC);

    sigprocmask(SIG_BLOCK, &s1, &s2);
    
    while (1) {
        struct signalfd_siginfo sss;
        read(fd, &sss, sizeof(sss));
        printf("%d\n", sss.ssi_signo);
    }
    // int c = getchar();
    // sleep(10);
    sigprocmask(SIG_UNBLOCK, &s1, NULL);
}
