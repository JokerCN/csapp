#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("usage: dd2hex.out <dotted decimal notation>\n");
        exit(1);
    }
    
    uint32_t host;
    int result;
    result = inet_pton(AF_INET, argv[1], &host);
    if(result == 0){
        printf("invalid dotted decimal\n");
        return 0;
    }
    else if(result < 0){
        printf("error: %s\n", strerror(errno));
        exit(1);
    }
    printf("0x%X\n", host);
    return 0;
}