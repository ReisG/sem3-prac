#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

int
main(int argc, char **argv)
{
    int file = creat(argv[1], 0777);

    unsigned short value;
    while (scanf("%hu", &value) == 1)
    {
        char buf[2];
        buf[0] = value >> 8;
        buf[1] = value & 0xff;
        write(file, buf, sizeof(buf));
    }
    close(file);
}