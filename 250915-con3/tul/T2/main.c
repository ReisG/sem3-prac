#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

int
main(int argc, char **argv)
{
    int file = open(argv[1], O_RDWR);
    lseek(file, 0, SEEK_SET);
    
    double bvalue, evalue;
    read(file, &bvalue, sizeof(bvalue));
    
    lseek(file, -sizeof(double), SEEK_END);
    read(file, &evalue, sizeof(evalue));

    
    lseek(file, -sizeof(double), SEEK_END);
    write(file, &bvalue, sizeof(bvalue));

    lseek(file, 0, SEEK_SET);
    write(file, &evalue, sizeof(evalue));

    close(file);
    return 0;
}