#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

struct Context
{
    int n;
    pthread_t *ids;
    pthread_mutex_t *ms;
    char *s;
};

struct Info
{
    int serial;
    struct Context *cntx;
};

void *
func(void *ptr)
{
    struct Info *ii = (struct Info *) ptr;
    int serial = ii->serial;
    int left = serial;
    int right = (serial + 1) % ii->cntx->n;
    while (1) {
        ii->cntx->s[serial] = 'T';
        // usleep(10000);
        ii->cntx->s[serial] = 'W';
        // dead lock occures when they all lock their left fork
        // therefore locking each other from picking right one
        pthread_mutex_lock(&ii->cntx->ms[left]);
        pthread_mutex_lock(&ii->cntx->ms[right]);
        ii->cntx->s[serial] = 'E';
        // usleep(10000);
        pthread_mutex_unlock(&ii->cntx->ms[right]);
        pthread_mutex_unlock(&ii->cntx->ms[left]);
        ii->cntx->s[serial] = 'T';
    }
}

int
main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "wrong args\n");
        exit(1);
    }

    struct Context cntx = {};

    printf("%zu\n", sizeof(pthread_mutex_t));
    cntx.n = strtol(argv[1], NULL, 10);
    cntx.ids = calloc(cntx.n, sizeof(cntx.ids[0]));
    cntx.ms = calloc(cntx.n, sizeof(cntx.ms[0]));
    cntx.s = malloc(cntx.n + 1);
    cntx.s[cntx.n] = 0;
    memset(cntx.s, ' ', cntx.n);
    for (int i = 0; i < cntx.n; ++i) {
        pthread_mutex_init(&cntx.ms[i], NULL);
    }

    struct Info *info = calloc(cntx.n, sizeof(info[0]));
    for (int i = 0; i < cntx.n; ++i) {
        info[i].serial = i;
        info[i].cntx = &cntx;
        pthread_create(&cntx.ids[i], NULL, func, &info[i]);
    }

    while (1) {
        printf("[%s]\n", cntx.s);
        usleep(100000);
    }

    for (int i = 0; i < cntx.n; ++i) {
        pthread_join(cntx.ids[i], NULL);
    }

    return 0;
}
