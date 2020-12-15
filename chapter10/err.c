#include "err.h"
#include <unistd.h>
#include <stdio.h>

// void sys_err(const char* message)
// {
//     fprintf(stderr, "error: %s, %s\n", strerror(errno), message);
//     _exit(1);
// }

void sys_err()
{
    fprintf(stderr, "error: %s\n", strerror(errno));
    _exit(1);
}