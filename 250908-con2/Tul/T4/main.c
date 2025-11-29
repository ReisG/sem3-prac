#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// kills nth symbol
void kill(char *str, int n)
{
    memcpy(str + n, str + n + 1, strlen(str + n + 1) + 1);
}

void insert(char *str, int n, char c)
{
    memmove(str + n + 1, str + n, strlen(str + n) + 1);
    str[n] = c;
}

int
main(void)
{
    char buf[1000] = "Hello how are you doing";
    insert(buf, 5, 'h');
    printf("%s", buf);
    return 0;
}