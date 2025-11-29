#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main(int args, char **argv)
{
    long res;
    char *p;
    errno = 0;
    res = strtol(argv[1], &p, 0);
    // ERANGE - overflow
    // did we read it correct??
    // empty string
    // if we want to read int.
    if (errno || *p || argv[1] == p || (int) res != res) {
        
    }
}
