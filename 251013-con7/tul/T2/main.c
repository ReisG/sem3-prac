#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/mman.h>

int
main(int argc, char **argv)
{
    // if (argc != 3)
    // {
    //     fprintf(stderr, "wrong number of args");
    //     exit(1);
    // }

    int fd1 = open(argv[1], O_RDWR, 0600);
    if (fd1 < 0)
    {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        exit(1);
    }

    int fd2 = open(argv[2], O_RDWR | O_CREAT, 0666);
    if (fd2 < 0)
    {
        close(fd1);
        fprintf(stderr, "cannot open file %s\n", argv[2]);
        exit(1);
    }

    struct stat buf = {};
    if (fstat(fd1, &buf) < 0)
    {
        close(fd1);
        close(fd2);
        fprintf(stderr, "cannot open fstat on %s\n", argv[1]);
        exit(1);
    }

    // projecting files in memory
    char *mfile1 = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, fd1, 0);
    if (mfile1 == MAP_FAILED)
    {
        fprintf(stderr, "cannot project %s to memory\n", argv[1]);
        close(fd1);
        close(fd2);
        exit(1);
    }
    close(fd1);

    ftruncate(fd2, buf.st_size);

    char *mfile2 = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
    if (mfile2 == MAP_FAILED)
    {
        close(fd2);
        munmap(mfile1, buf.st_size);
        fprintf(stderr, "cannot project %s to memory\n", argv[2]);
        exit(1);
    }
    close(fd2);

    memcpy(mfile2, mfile1, buf.st_size);
    munmap(mfile1, buf.st_size);
    munmap(mfile2, buf.st_size);

    return 0;
}