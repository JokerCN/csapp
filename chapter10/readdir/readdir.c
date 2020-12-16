#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include "err.h"

int main(int argc, char **argv)
{
    DIR *streamp;
    struct dirent *dep;

    streamp = opendir(argv[1]);

    errno = 0;
    while((dep = readdir(streamp)) != NULL) {
        printf("Found file; %s\n", dep ->d_name);
    }

    if(errno != 0)
        sys_err();
    
    closedir(streamp);
    return 0;
}