#include <stdio.h>
#include <time.h>

#include <string.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "wrong args\n");
        exit(1);
    }

    char *end = NULL;
    int year = strtol(argv[1], &end, 10);
    int day = strtol(argv[2], &end, 10);
    int wday = strtol(argv[3], &end, 10);

    int res = 0;
    for (int i = 0; i < 12; i++) {
        // we cant add just months
        struct tm buf = {};
        buf.tm_year = year - 1900;
        buf.tm_mday = day;
        buf.tm_mon = i;
        buf.tm_isdst = -1;
        mktime(&buf);
        if (buf.tm_mon != i) {
            continue;
        }

        if (buf.tm_wday == wday) {
            res++;
        }
    }

    printf("%d\n", res);
    return 0;
}
