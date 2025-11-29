#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>

#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

int
main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "wrong nubmer of args\n");
        exit(1);
    }

    struct stat buf = {};
    if (stat(argv[1], &buf) < 0)
    {
        fprintf(stderr, "cannot read stat from file %s\n", argv[1]);
        exit(1);
    }

    int fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        exit(1);
    }

    char *file = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (file == MAP_FAILED)
    {
        close(fd);
        fprintf(stderr, "cannot project file to memory\n");
        exit(1);
    }

    close(fd);

    for (off_t i = 0; i < buf.st_size / 2; i++)
    {
        char temp = file[buf.st_size - 1 - i];
        file[buf.st_size - 1 - i] = file[i];
        file[i] = temp;
    }

    munmap(file, buf.st_size);
    return 0;
}