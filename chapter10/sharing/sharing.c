#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    int fd, readr;
    char c;
    pid_t pid;

    if((fd = open("foobar.txt", O_RDONLY, 0)) < 0){
        printf("can not open file foobar.txt: %s\n", strerror(errno));
        exit(1);
    }

    if((pid = fork()) == 0){ /* child process */
        if((readr = read(fd, &c, 1) < 0)){
            printf("can not read file: %s\n", strerror(errno));
            exit(1);
        }
        exit(0);
    }
    else if(pid > 0)/* parent process */
    {
        if((pid = wait(NULL)) < 0){
            printf("wait error: %s\n", strerror(errno));
            exit(1);
        }
        if((readr = read(fd, &c, 1) < 0)){
            printf("can not read file: %s\n", strerror(errno));
            exit(1);
        }
        printf("c = %c\n", c);
    }
    else
    {
        printf("can not fork new process: %s\n", strerror(errno));
    }

    return 0;
}