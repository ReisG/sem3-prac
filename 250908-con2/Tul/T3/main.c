#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int
sum1(int v1, int v2)
{
    int res;
    int addchk = __builtin_sadd_overflow(v1, v2, &res);
    if (addchk) {
        int int_max = ~0u >> 1;
        res = (v1 > 0 ? int_max : ~int_max);
    }
    return res;
}

int
main(void)
{
    int a = INT_MAX, b = INT_MAX;
    printf("%d\n", sum(a, b));
    return 0;
}