#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

int
main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "wrong args\n");
        exit(1);
    }

    char *end = NULL;
    errno = 0;
    int cache_size = strtol(argv[1], &end, 10);
    if (errno || end == argv[1] || *end != '\0') {
        fprintf(stderr, "cannot read cache_size\n");
        exit(1);
    }

    end = NULL;
    errno = 0;
    int block_size = strtol(argv[2], &end, 10);
    if (errno || end == argv[1] || *end != '\0') {
        fprintf(stderr, "cannot read block_size\n");
        exit(1);
    }

    int cache_blocks = cache_size / block_size;
    int *cache = calloc(cache_size, sizeof(*cache));
    if (cache == NULL) {
        fprintf(stderr, "cannot allocate memory\n");
        exit(1);
    }
    memset(cache, -1, cache_blocks * sizeof(*cache));

    int addr = 0;
    int miss = 0;
    while (scanf("%x", &addr) == 1) {
        int blk = addr / block_size;
        int cache_blk = blk % cache_blocks;
        printf("Requested %d, placed %d ", blk, cache_blk);

        if (cache[cache_blk] != -1 && cache[cache_blk] != blk) {
            miss++;
            printf("miss\n");
        }
        else
        {
            printf("hit\n");
        }
        cache[cache_blk] = blk;
    }

    free(cache);
    printf("%d\n", miss);
    return 0;
}
