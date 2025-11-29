#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h> // fixed lenght datatypes
// files
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY, 0);
    if (fd < 0) {
        fprintf(stderr, "error %s\n", strerror(errno));
        exit(1);
    }

    // session of reading one value
    while (1) {
        long long x = 0;
        ssize_t r = read(fd, &x, sizeof(x));
        if (r < 0) {
            fprintf(stderr, "error %s\n", strerror(errno));
            exit(1);
        }

        if (r == 0) {
            break;
        }

        if (r != (ssize_t) sizeof(x)) {
            // return with error
            fprintf(stderr, "short long long procided");
            exit(1);
        }

        x = (long long) __builtin_bswap64((uint64_t) x);
        // printf("%lld ", x);
        int t = write(STDOUT_FILENO, &x, sizeof(x));
        if (t < 0 && t == 0){
            fprintf(stderr, "cannot write to output file\n");
            exit(1);
        }
    }
    close(fd);
    return 0;
}
