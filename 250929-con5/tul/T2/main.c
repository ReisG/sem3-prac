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

    DIR *d = opendir(argv[1]);
    if (!d) {
        abort();
    }

    struct dirent *dd;

    while (dd = readdir(d)) {
        char path[PATH_MAX] = "";
        snprintf(path, PATH_MAX, "%s/%s", argv[1], dd->d_name);
        if (access(path, W_OK) < 0) {
            continue;
        }

        struct stat buf;
        if (lstat(path, &buf) < 0) {
            continue;
        }
        if (!S_ISREG(buf.st_mode)) {
            continue;
        }

        size_t namesz = strlen(dd->d_name);
        if (namesz > 0 && dd->d_name[namesz - 1] == '~' 
            || namesz >= 4 && strcmp(dd->d_name + namesz - 4, ".bak") == 0) {
            unlink(path);
        }
    }

    closedir(d);
    return 0;
}
