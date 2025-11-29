#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

/*
Create n processes. Assume each of them has id from 1 to n. 
Make each process to print its' it. Make values be printed in descending order.
*/

int
main(int argc, char **argv)
{
    char *end = NULL;
    int n = strtol(argv[1], &end, 10);

    int i = 1;
    while (i < n) {
        pid_t pid = fork();
        if (pid != 0) {
            while (wait(NULL) != -1);
            break;
        }
        i++;
    }

    printf("%d\n", i);
    while(wait(NULL) != -1);
    return 0;
}
