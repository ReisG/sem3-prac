#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    char buf[10000];
    while (fgets(buf, sizeof(buf), stdin)) {
        int clen = 0;
        char *nowstr = buf;
        double nubmer;
        double sum = 0;
        while (sscanf(nowstr, "%lf%n", &nubmer, &clen) == 1) {
            sum += nubmer;
            nowstr += clen;
        }
        printf("%g\n", sum);
    }
    return 0;
}
