#include <stdio.h>
#include <unistd.h>

int
main(void)
{
    long long x;
    while (scanf("%lld", &x) == 1) {
        ssize_t w = write(STDOUT_FILENO, &x, sizeof(x));
        if (w != (ssize_t) sizeof(x))
        {
            fprintf(stderr, "...error");
            abort();
        }
    }
}
