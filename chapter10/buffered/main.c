#include "rio.h"
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char **argv)
{
    if(argc < 2){
        printf("usage: main.out <input file>.\n");
        exit(0);
    }

    rio_t t;
    int fd;
    ssize_t rio_result;
    char buf[BUF_SIZE];
    if((fd = open(argv[1], O_RDONLY, 0)) == -1){
        sys_err();
    }

    rio_readinitb(&t, fd);
    while((rio_result = rio_readlineb(&t, buf, BUF_SIZE)) > 0){
        printf("%s", buf);
    }

    if(rio_result < 0)
        sys_err();
    
    close(fd);
    return 0;
}