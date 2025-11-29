#include <stdio.h>

#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *
thread_func(void *p)
{
    /*_Atomic*/ int *pp = p;
    printf("%d\n", *pp);
    for (int i = 0; i < 10000000; ++i) {
        pthread_mutex_lock(&m);
        (*pp)++;
        pthread_mutex_unlock(&m);
    }
    return pp;
}

int
main(int argc, char **argv)
{
    /*_Atomic*/ int x = 100;
    pthread_t t;
    pthread_create(&t,          // address of new thread stored
                   NULL,        // stack cannot be changed
                   thread_func, // function pointer to
                   (void *) &x  // function args
    );

    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&m);
        x++;
        pthread_mutex_unlock(&m);
    }

    void *ret = NULL;
    pthread_join(t, &ret);

    printf("%ld %ld %d\n", (long) ret, (long) &x, x);
    return 0;
}
