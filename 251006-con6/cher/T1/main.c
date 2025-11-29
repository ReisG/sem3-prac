#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <dirent.h>

#define stack(T)                                                                                                       \
    struct                                                                                                             \
    {                                                                                                                  \
        size_t sz, cap;                                                                                                \
        T *arr;                                                                                                        \
    }

#define stack_push(obj, val)                                                                                           \
    do {                                                                                                               \
        if ((obj).sz == (obj).cap) {                                                                                   \
            if (!(obj).cap) { /* if it only created*/                                                                  \
                (obj).cap = 1;                                                                                         \
                (obj).arr = calloc((obj).cap, sizeof(*(obj).arr));                                                     \
                if (!(obj).arr) {                                                                                      \
                    fprintf(stderr, "cannot allocate space\n");                                                        \
                    exit(1);                                                                                           \
                }                                                                                                      \
            } else { /* now need to resize capacity*/                                                                  \
                (obj).cap <<= 1;                                                                                       \
                void *t = reallocarray((obj).arr, (obj).cap, sizeof(*(obj).arr));                                      \
                if (!t) {                                                                                              \
                    fprintf(stderr, "cannot allocate memory: %lu bytes needed\n", (obj).cap * sizeof(*(obj).arr));     \
                    free((obj).arr);                                                                                   \
                    exit(1);                                                                                           \
                }                                                                                                      \
                (obj).arr = t;                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
        (obj).arr[(obj).sz++] = (val);                                                                                 \
    } while (0)

#define stack_top(obj)                                                                                                 \
    ({                                                                                                                 \
        if ((obj).sz == 0) {                                                                                           \
            fprintf(stderr, "cannot pop value from array\n");                                                          \
            exit(1);                                                                                                   \
        }                                                                                                              \
        (obj).arr[(obj).sz - 1];                                                                                       \
    })

#define stack_pop(obj)                                                                                                 \
    do {                                                                                                               \
        if ((obj).sz == 0) {                                                                                           \
            fprintf(stderr, "cannot pop element from the top of the stack\n");                                         \
            exit(1);                                                                                                   \
        }                                                                                                              \
        (obj).sz--;                                                                                                    \
        if ((obj).sz < obj.cap >> 2) {                                                                                 \
            /*if obj.sz < obj.cap / 4 resizing*/                                                                       \
            (obj).cap >>= 1;                                                                                           \
            errno = 0;                                                                                                 \
            void *t = reallocarray((obj).arr, (obj).cap, sizeof(*(obj).arr));                                          \
            if (!t || errno) {                                                                                         \
                fprintf(stderr, "problems allocating memory: %s\n", strerror(errno));                                  \
                exit(1);                                                                                               \
            }                                                                                                          \
            (obj).arr = t;                                                                                             \
        }                                                                                                              \
    } while (0)

#define stack_free(obj)                                                                                                \
    do {                                                                                                               \
        free((obj).arr);                                                                                               \
        (obj).sz = 0; /*setting everything to zero in vector*/                                                         \
        (obj).cap = 0;                                                                                                 \
        (obj).arr = NULL;                                                                                              \
    } while (0)

void
traverse(const char *dir, void *user, void (*handler)(const char *))
{
    stack(char *) files;

    DIR *d = opendir(dir);
    if (!d) {
        // we have no rights to open this folder
        return;
    }

    struct dirent *dd;
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        stack_push(files, strdup(dd->d_name));
    }
    closedir(d);

    for (size_t i = 0; i < files.sz; ++i) {
        char *path = NULL;
        asprintf(&path, "%s/%s", dir, files.arr[i]);
        // printf("%s\n", path);
        handler(user, path);
        free(files.arr[i]);

        struct stat stb;
        if (lstat(path, &stb) < 0) {
            continue;
        }

        if (S_ISDIR(stb.st_mode)) {
            traverse(path);
        }
    }

    stack_free(files);
}

void
handler(void *user, const char *path)
{
    printf("%s %s\n", path, (const char *) user);
}

int
main(int argc, char *argv[])
{
    traverse(argv[1], handler);
}
