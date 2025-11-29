#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>

int
main(int argc, char **argv)
{
    char chooseflag[] = "rwx";

    // reading metadata
    struct stat buf;
    lstat(argv[1], &buf);

    if (S_ISDIR(buf.st_mode)) putchar('d');
    else if (S_ISLNK(buf.st_mode)) putchar('l');
    else putchar('-');

    unsigned short now = 1 << 8;
    for (int i = 0; i < 9; i++)
    {
        if (buf.st_mode & now) putchar(chooseflag[i % 3]);
        else putchar('-');
        now >>= 1;
    }

    putchar(' ');

    printf("%lu %u %u %ld %s\n", 
        buf.st_nlink, 
        buf.st_uid, 
        buf.st_gid, 
        buf.st_size, 
        argv[1]);

    return 0;
}