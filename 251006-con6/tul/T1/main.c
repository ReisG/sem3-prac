#include <time.h>
#include <stdio.h>

void
f(int *year, int *mon, int *day,
  int offset) // in days
{
    struct tm buf = {};
    buf.tm_year = *year - 1900;
    buf.tm_mon = *mon - 1;
    buf.tm_mday = *day + offset;
    buf.tm_isdst = -1;
    mktime(&buf);

    *year = buf.tm_year + 1900;
    *mon = buf.tm_mon + 1;
    *day = buf.tm_mday;
}

int
main(void)
{
    int arr[] = {1900, 1, 1};
    f(arr, arr + 1, arr + 2, 10);
    printf("%d %d %d", arr[0], arr[1], arr[2]);
    return 0;
}
