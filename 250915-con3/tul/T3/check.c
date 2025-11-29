#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

int
main(int argc, char **argv)
{
    int file = open(argv[1], O_RDONLY);
    
    char buf[2];
    while (read(file, &buf, sizeof(buf)))
    {
        printf("%x%x ", buf[0], buf[1]);
    }
}