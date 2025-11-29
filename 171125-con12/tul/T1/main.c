#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>

#include <sys/ipc.h>
#include <sys/sem.h>

#include <sys/shm.h>
/* father creates shm and sem arr
    child1 reads ints from stdin
    child2 writes value to stdion that was stored in shm
*/

int
main(int argc, char **argv)
{
    int semarr_id = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    int shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

    int *p = shmat(shm_id, NULL, 0);

    // {
    //     struct sembuf allow_write = {0, 1, SEM_UNDO};
    //     semop(semarr_id, &allow_write, 2);
    // }

    pid_t pid = 0;

    pid = fork();
    if (pid == 0)
    {
        // reading child
        int x = 0;
        while (scanf("%d", p) == 1)
        {
            // *p = x;
            struct sembuf allow_to_read = {1, 1, SEM_UNDO};
            semop(semarr_id, &allow_to_read, 1);
            struct sembuf go_and_write = {0, -1, SEM_UNDO}; 
            semop(semarr_id, &go_and_write, 1);
        }
        semctl(semarr_id, 0, IPC_RMID, 0);
        return 0;
    }

    pid = fork();
    if (pid == 0)
    {
        // reading process
        struct sembuf go_and_read = {1, -1, SEM_UNDO};
        while (semop(semarr_id, &go_and_read, 1) != -1)
        {
            int x = *p;
            printf("%d\n", x);
            struct sembuf allow_write = {0, 1, SEM_UNDO};
            semop(semarr_id, &allow_write, 1);
        }
        return 0;
    }

    while (wait(NULL) != -1);
    shmctl(shm_id, IPC_RMID, 0);
    return 0;
}
