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
    if (argc != 2) {
        fprintf(stderr, "args wrong\n");
        abort();
    }

    unsigned long long res = 0;
    DIR *d = opendir(argv[1]);
    struct dirent *dd;
    while (dd = readdir(d)) {
        char path[PATH_MAX] = "";
        strcat(path, argv[1]);
        strcat(path, "/");
        strcat(path, dd->d_name);

        struct stat buf;
        if (lstat(path, &buf) < 0) {
            puts(path);
            abort();
        }
        if (S_ISREG(buf.st_mode)) {
            res += buf.st_size;
        }

    }

    printf("%lu\n", res);
    closedir(d);
}
