#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

int
main(int argc, char **argv)
{
    int f = open(argv[1], O_RDWR);

    if (argv[2][0] == 'w')
    {
        // for (int i = 0; i < 10; i++)
        // {
        //     double t = i;
        //     write(f, &t, sizeof(t));
        // }
        double t[10];
        for (int i = 0; i < sizeof(t) / sizeof(*t); i++)
        {
            t[i] = i;
        }
        write(f, &t, sizeof(t));
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            double val;
            read(f, &val, sizeof(double));
            printf("%lf ", val);
        }
        // int cnt;
        // double val;
        // while (cnt = read(f, &val, sizeof(val)))
        // {
        //     printf("%lf ", val);
        // }
    }

    close(f);
    return 0;
}