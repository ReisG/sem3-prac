#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

int
main(int argc, char **argv)
{
    int src = open(argv[1], O_RDONLY);
    
    int mod;
    sscanf(argv[3], "%o", &mod);

    int dst = creat(argv[2], mod);

    char buf[1024];
    size_t cnt;
    while (cnt = read(src, buf, sizeof(buf)))
    {
        char *p = buf;
        while (cnt)
        {
            int wn = write(dst, p, cnt);
            cnt -= wn;
            p += wn;
        }
    }

    close(src);
    close(dst);
    return 0;
}
