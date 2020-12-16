#include "err.h"
#include <unistd.h>
#include <stdio.h>

void sys_err(int a)
{
    fprintf(stderr, "error: %s\n", strerror(errno));
    _exit(1);
}