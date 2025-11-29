/*
Might not work properly
*/

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/mman.h>

int
main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "wrong nubmer of args\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR, 0600);
    if (fd < 0) {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        exit(1);
    }

    struct stat buf = {};
    if (fstat(fd, &buf) < 0) {
        close(fd);
        fprintf(stderr, "cannot read stat of file %s\n", argv[1]);
        exit(1);
    }

    if (buf.st_size == 0)
    {
        // there nothing to execute
        close(fd);
        return 0;
    }

    if (buf.st_size % sizeof(int))
    {
        // wrong format of file
        fprintf(stderr, "wrong file format provided\n");
        close(fd);
        exit(1);
    }

    // extending file capacity
    size_t newsz = buf.st_size + sizeof(int);
    if (ftruncate(fd, newsz) < 0) {
        close(fd);
        fprintf(stderr, "cannot shrik file %s no fit max\n", argv[1]);
        exit(1);
    }

    // projecting
    int *filem = mmap(NULL, newsz, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (filem == MAP_FAILED) {
        close(fd);
        fprintf(stderr, "cannot project file %s to memory\n", argv[1]);
        exit(1);
    }
    close(fd);

    // NOTE: there might be a problem if size is 0;
    // moving values further by one
    memmove(filem + 1, filem, buf.st_size);

    // searching for max in array
    int nowmax = filem[1];
    for (size_t i = 2; i < buf.st_size; i++) {
        if (nowmax < filem[i]) nowmax = filem[i];
    }
    filem[0] = nowmax;

    munmap(filem, buf.st_size);
    return 0;
}
