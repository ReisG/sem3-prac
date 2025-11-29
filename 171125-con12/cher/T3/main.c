#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

void *
thread_func(void *p)
{
    int pp = (int) (intptr_t) p;
    printf("%d\n", pp);
    // free(p);
    return NULL;
}

enum
{
    COUNT = 10
};
int
main(void)
{
    [[maybe_unused]]
    int x = 100;

    pthread_t th[COUNT];
    [[maybe_unused]] int v[COUNT];

    for (int i = 0; i < COUNT; i++) {
        v[i] = i;
        // we need to be sure that calloc's memery is not freed
        // until thread stopped using it
        // int *p = malloc(sizeof(*p)); // now we free memory when we are inside thread function
        // *p = i;
        pthread_create(&th[i], NULL, thread_func, (void *)(intptr_t) i);
        // free(p);
    }

    for (int i = 0; i < COUNT; i++) {
        pthread_join(th[i], NULL);
    }
}
