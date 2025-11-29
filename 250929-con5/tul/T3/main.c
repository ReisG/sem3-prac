#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>
#include <string.h>

#include <dirent.h>

int
main(int argc, char **argv)
{
    if (argc != 1) {
        abort();
    }

    DIR *d = opendir("..");
    if (!d) {
        abort();
    }

    struct stat buf = {};
    if (lstat(".", &buf) < 0) {
        abort();
    }

    struct stat bufroot = {};
    if (lstat("/", &buf) < 0) {
        abort();
    }

    if (buf.st_dev == bufroot.st_dev && buf.st_ino == bufroot.st_ino)
    {
        putc("/");
        return 0;
    }

    struct dirent *dd;
    while (dd = readdir(d)) {
        char path[PATH_MAX] = "";
        snprintf(path, sizeof(path), "../%s", dd->d_name);

        struct stat fold = {};
        if (lstat(path, &fold) < 0) {
            continue;
        }

        if (fold.st_dev == buf.st_dev && fold.st_ino == buf.st_ino) {
            puts(dd->d_name);
            return 0;
        }
    }

    fprintf(stderr, "cannot find\n");
    abort();
}
