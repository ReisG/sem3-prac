#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>

int
main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "wrong args: %d/2\n", argc - 1);
        exit(1);
    }

    DIR *dsrc = opendir(argv[1]);
    if (!dsrc) {
        fprintf(stderr, "cannot open src directory\n");
        exit(1);
    }

    struct dirent *dd = NULL;
    while ((dd = readdir(dsrc))) {
        char *path = NULL;
        asprintf(&path, "%s/%s", argv[1], dd->d_name);

        struct stat buf = {};
        if (lstat(path, &buf) < 0) {
            continue;
        }
        
        if (!S_ISREG(buf.st_mode))
        {
            continue;
        }

        if (time(NULL) - buf.st_mtime < 60 * 60 * 24 * 7 * 2)
        {
            char *path2 = NULL;
            asprintf(&path2, "%s/%s", argv[2], dd->d_name);
            rename(path, path2);
            free(path2);
        }
        free(path);
    }

    closedir(dsrc);
    return 0;
}