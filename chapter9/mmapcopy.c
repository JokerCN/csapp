#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 4096

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "usage: mmapcopy.out <file_name>\n");
        exit(1);
    }

    int fd;
    if((fd = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "open file %s failed: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    struct stat stat_buf;
    if(stat(argv[1], &stat_buf) < 0){
        fprintf(stderr, "stat file %s failed: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    int i = 0;
    void* bufp;
    while(i < stat_buf.st_size){
        bufp =(void*)mmap(NULL, BUFSIZE, PROT_READ, MAP_PRIVATE, fd, i);
        if(bufp == MAP_FAILED){
            fprintf(stderr, "mmap failed: %s\n", strerror(errno));
            exit(1);
        }
        if(write(STDOUT_FILENO, bufp, BUFSIZE) < 0){
            fprintf(stderr, "write failed: %s\n", strerror(errno));
            munmap(bufp, BUFSIZE);
            exit(1);
        }

        munmap(bufp, BUFSIZE);
        i = i + BUFSIZE;
    }

    close(fd);
    return 0;
}

