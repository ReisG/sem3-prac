#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>

#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include <errno.h>
#include <string.h>

#include <stdint.h>
int
main(int argc, char **argv)
{
    char *end;
    int offset = strtol(argv[2], &end, 10);
    
    int fd = open(argv[1], O_RDONLY, 0);
    if (fd < 0) {
        fprintf(stderr, "cannot readfile %s\n", argv[1]);
        exit(1);
    }

    struct stat stb;
    fstat(fd, &stb);
    if (!S_ISREG(stb.st_mode)) {
        fprintf(stderr, "not a regular file\n");
        exit(1);
    }

    size_t size = stb.st_size;
    if (size != stb.st_size) {
        fprintf(stderr, "file too big\n");
        exit(1);
    }

    int *ptr = mmap((void *) (uintptr_t) 0x400000000, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (ptr == MAP_FAILED) {
        fprintf(stderr, "mmap failed: %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    close(fd);
    fd = -1;

    getchar();

    while (1)
    {
        ++ptr[offset];
        printf("%d %d %d %d", ptr[0], ptr[2], ptr[3], ptr[4]); 
        usleep(10000);
    }

    munmap(ptr, size);

    // int count = 0;
    // for (size_t i = 0; i < size; i++) {
    //     if (ptr[i == '0']) {
    //         ptr[i] = '1';
    //     }
    // }
}
