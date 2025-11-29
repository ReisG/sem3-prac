#include <stdio.h>
#include <stdlib.h>

#include <sys/msg.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "wrong args\n");
        exit(1);
    }

    int MAXPROC = 0;
    char *end = NULL;
    errno = 0;
    MAXPROC = strtol(argv[1], &end, 10);
    if (errno || end == argv[1] || *end != '\0') {
        fprintf(stderr, "cannot read first nunber");
        exit(1);
    }

    errno = 0;
    end = NULL;
    int n = strtol(argv[2], &end, 10);
    if (errno || end == argv[1] || *end != '\0') {
        fprintf(stderr, "cannot read second nunber");
        exit(1);
    }

    int msgq = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (msgq < 0) {
        fprintf(stderr, "cannot create msgqueue");
        return 0;
    }

    struct Data
    {
        long type;
        int value;
    };

    struct Data buf = {.type = 1, .value = 1};
    if (msgsnd(msgq, &buf, sizeof(buf) - sizeof(long), 0) < 0)
    {
        fprintf(stderr, "cannot send first message\n");
        exit(1);
    }

    int id = 1;
    for (; id <= MAXPROC; id++) {
        pid_t pid = fork();
        if (pid == -1) {
            msgctl(msgq, IPC_RMID, NULL); // don't know what to do here
            kill(SIGKILL, 0);
        } else if (pid == 0) {
            struct Data buf = {};
            while (msgrcv(msgq, &buf, sizeof(buf) - sizeof(long), id, 0) >= 0) {
                printf("%d %d\n", id, buf.value);
                fflush(stdout);
                if (buf.value == n) {
                    msgctl(msgq, IPC_RMID, NULL);
                    return 0;
                }
                buf = (struct Data) {.type = (id % MAXPROC) + 1, .value = buf.value + 1};
                msgsnd(msgq, &buf, sizeof(buf) - sizeof(long), 0);
            }
            return 0;
        }
    }

    while (wait(NULL) != -1) {
    }
}
