#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int fd[2];
    pid_t fo;
    char size[200000];


    if (pipe(fd) < 0)
        exit(1);

    fo = fork();
    if (fo == 0)
    {
        close(fd[0]);
        write(fd[1],"Nietzshe", 9);
        close(fd[1]);
    }
    else{
        close(fd[1]);
        read(fd[0], size, 9);
        close(fd[0]);
        printf("%s\n", size);
    }
}