#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

int
my_access(const char *name, int mode)
{
    struct stat buf;
    if (stat(name, &buf) < 0) {
        return -1;
    }
    if (mode == 0) {
        return 0; // just exists
    }

    unsigned short block = 0;
    if (getuid() == buf.st_uid) {
        block = (buf.st_mode >> 6) & 7;
    } else if (getgid() == buf.st_gid) {
        block = (buf.st_mode >> 3) & 7;
    } else {
        block = buf.st_mode & 7;
    }

    if ((block & mode) == mode) return 0;
    return -1;
}

int
main(int argc, char **argv)
{
    char *t;
    int mode = strtol(argv[2], &t, 8);
    printf("%d", my_access(argv[1], mode));
    return 0;
}
