#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>

#include <sys/wait.h>

int
main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "wrong nubmer of args\n");
        exit(1);
    }

    char *end = NULL;
    int n = strtol(argv[1], &end, 10);

    // creating file
    int f = open("file.bin", O_WRONLY | O_TRUNC | O_CREAT, 0666);
    if (f < 0) {
        fprintf(stderr, "cannot create file\n");
        exit(1);
    }

    close(f);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            int f = open("file.bin", O_RDWR);
            if (f < 0) {
                fprintf(stderr, "cannot open file\n");
                _exit(1);
            }
            pid = getpid();
            lseek(f, (n - i - 1) * sizeof(i), SEEK_SET);
            write(f, &i, sizeof(i));
            close(f);
            return 0;
        }
    }

    while (wait(NULL) != -1) {
    }

    return 0;
}
