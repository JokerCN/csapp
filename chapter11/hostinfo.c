#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <memory.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define GET_ADDR(x) (uint32_t*)(((char*)(&(*(x)-> sa_data)))+2)

int main(int argc, char **argv)
{
    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;
    char addr[16];

    if(argc != 2){
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM; /* Connections only */
    if((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0){
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    /* Walk the list and display each IP address */
    flags = NI_NUMERICHOST;  /* Display address string instead of domain name */
    for(p = listp; p; p = p -> ai_next){
        getnameinfo(p -> ai_addr, p -> ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        inet_ntop(AF_INET, GET_ADDR(p -> ai_addr), addr, 15);
        printf("addr: %s, host: %s\n", addr, buf);
    }

    /* Clean up */
    freeaddrinfo(listp);

    exit(0);
}