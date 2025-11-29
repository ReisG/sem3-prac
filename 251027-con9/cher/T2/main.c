#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <string.h>
#include <errno.h>

#include <fcntl.h>

int
main(int argc, char **argv)
{
    int pid = fork();
    if (!pid) {
        // close(STDOUT_FILENO); // freeing file descriptor with id 1
        // replacing space for file decriptor
        // with file
        int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0600);
        // if (fd != 1) abort();

        // replacing it manually
        dup2(fd, STDOUT_FILENO);

        // closing to not to be leaked
        // close(fd); // don't need to close due to O_CLOEXEC

        // unsafe, slow
        execl("/bin/sh", "sh", "-c", argv[1], NULL);

        // execlp(argv[1], argv[1], NULL);
        fprintf(stderr, "error: %s: %s\n", argv[1], strerror(errno));
        _exit(1);
    }

    wait(NULL);
}
