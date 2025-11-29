// conditional variable
// condvar
// mutex

#include <stdio.h>
#include <pthread.h>

struct Data
{
    pthread_mutex_t m;
    pthread_cond_t c;
    int rdcount, wrcount;
};

void
rwlock_rdlock(struct Data *p)
{
    pthread_mutex_lock(&p->m);
    while (p->wrcount > 0) {
        pthread_cond_wait(&p->c, &p->m);
    }
    ++p->rdcount;
    pthread_mutex_unlock(&p->m);
}

void
rwlock_wrlock(struct Data *p)
{
    pthread_mutex_lock(&p->m);
    while (p->wrcount > 0 || p->rdcount > 0) {
        // release mutex until I wake up
        pthread_cond_wait(&p->c, &p->m);
        // when I wakeup I lock mutex automatically
    }
    ++p->rdcount;
    pthread_mutex_unlock(&p->m);
}

void
rwlock_unlock(struct Data *p)
{
    pthread_mutex_lock(&p->m);
    if (p->wrcount > 0) {
        --p->wrcount;
    } else {
        --p->rdcount;
    }
    if (p->wrcount == 0 && p->rdcount == 0) {
        pthread_cond_broadcast(&p->c);
    }
    pthread_mutex_unlock(&p->m);
}

int
main(void)
{
}
