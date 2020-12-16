#include <sys/stat.h>
#include "err.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if(argc < 2){
        printf("usage: main.out <filename>\n");
        exit(1);
    }

    struct stat buf;
    char *type, *readok;
    if(stat(argv[1], &buf)<0){
        sys_err();
    }

    if(S_ISREG(buf.st_mode)) /* determine file type */
        type = "regular";
    else if((S_ISDIR(buf.st_mode)))
        type = "directory";
    else
        type = "other";

    if(buf.st_mode & S_IRUSR) /* check read access */
        readok = "yes";
    else
        readok = "no";

    printf("type: %s, read: %s\n", type, readok);

    return 0;
}