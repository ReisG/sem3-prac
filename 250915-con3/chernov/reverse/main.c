#include <stdio.h>
#include <stdlib.h>

#define  VEC_T(T) \
struct \
{ \
    size_t capacity; \
    size_t count; \
    T *data; \
} \

#define VEC_PUSH(vec, value) \
do { \
    if ((vec.capacity) == (vec).count) { \
        if ((vec).capacity == 0) (vec).capacity++; \
        size_t nc = (vec).capacity << 1; \
        if (nc < (vec).capacity) abort(); \
        void *nd = reallocarray((vec).data, nc, sizeof((vec).data[0])); \
        if (!nd) abort(); \
        (vec).capacity = nc; \
        (vec).data = nd; \
    } \
    (vec).data[(vec).count++] = (value); \
} while (0) \


int
main(int argc, char **argv)
{
    int val = 0;

    VEC_T(int) vec = {};

    for (int i = 1; i < argc; i++)
    {
        FILE *fin_file = fopen(argv[i], "r");
        if (!fin_file) {
            fprintf(stderr, "cannot open file %s\n", argv[i]);
            free(vec.data);
            exit(1);
        }

        int val = 0;
        while (fscanf(fin_file, "%d", &val) == 1){
            VEC_PUSH(vec, val);
        }

        fclose(fin_file);
    }

    for (size_t i = vec.count; i > 0; i--) {
        printf("%d ", vec.data[i - 1]);
    }
    printf("\n");

    free(vec.data);
    return 0;
}
