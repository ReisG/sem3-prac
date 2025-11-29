#include <pthread.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    pthread_t th1 = pthread_self();

    printf("%ld\n", (long) th1);

    // don't use it
    // pthread_cancel(th1);
    pthread_exit(NULL);

    return 0;
}