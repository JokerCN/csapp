#include <netdb.h>
#include <memory.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int open_clientfd(char *hostname, char* port){
    int clientfd, rc;
    struct addrinfo hints, *listp, *p;

    /* get a list of potential server addresses */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM; /* Open a connection */
    hints.ai_flags = AI_NUMERICSERV; /* using a numeric port arg */
    hints.ai_flags |= AI_ADDRCONFIG; /* recommended for connections */
    if((rc = getaddrinfo(hostname, port, &hints, &listp)) != 0){
        fprintf(stderr, "error: %s\n", gai_strerror(rc));
        return -1;
    }

    /* walk the list for one that we can successfully connect to */
    for(p = listp; p; p = p -> ai_next){
        /* Create a socket descriptor */
        if((clientfd = socket(p->ai_family, p -> ai_socktype, p->ai_protocol)) < 0)
            continue; /* socket failed, try the next */
        
        /* connect to the server */
        if(connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break; /* success */
        if (close(clientfd) < 0) { /* Connect failed, try another */  //line:netp:openclientfd:closefd
            fprintf(stderr, "open_clientfd: close failed: %s\n", strerror(errno));
            return -1;
        }
    }

    /* clean up */
    freeaddrinfo(listp);
    if(!p) /* All connects failed */
        return -1;
    else 
        return clientfd;

}