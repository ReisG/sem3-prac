#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
// #include <sys/file.h>
#include <sys/types.h>

#include <sys/mman.h>
#include <sys/wait.h>

int
main(int argc, char **argv)
{
    char *end = NULL;
    int n = strtol(argv[1], &end, 10);

    int f = open("file.bin", O_RDWR | O_TRUNC | O_CREAT, 0666);
    if (f < 0) {
        exit(1);
    }

    size_t len = n * sizeof(int);
    if (ftruncate(f, len) < 0) {
        exit(1);
    }

    int *arr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
    if (arr == MAP_FAILED) {
        close(f);
        exit(1);
    }
    close(f);

    printf("I have allocated memspace\n");

    for (int i = 0; i < n; i++) {
        printf("Process created %i\n", i);
        pid_t pid;
        do {
            pid = fork();
        } while (pid == -1);
        if (pid == 0) {
            // child
            arr[n - i - 1] = i;
            return 0;
        }
    }

    while (wait(NULL) != -1)
        ;

    munmap(arr, len);
    return 0;
}
