#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "rio.h"
#include "err.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

static char buf[] = "abcdefghijklmn\n";

int main(){
    int fd;
    char *pbuf2;
    size_t n = strlen(buf);
    umask(DEF_UMASK);
    if((fd = open("a.txt", O_RDWR|O_CREAT, DEF_MODE)) < 0)
        sys_err();
    
    rio_writen(fd, buf, n);
    pbuf2 = (char*)malloc(n + 1);
    lseek(fd, 0, SEEK_SET);
    rio_readn(fd, pbuf2, n);
    printf("result: %s", pbuf2);
    return 0;
}