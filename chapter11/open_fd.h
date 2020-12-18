#ifndef _OPEN_FD_H
#define _OPEN_FD_H

#include <fcntl.h>

int open_listenfd(char *port);
int open_clientfd(char *hostname, char* port);

#endif