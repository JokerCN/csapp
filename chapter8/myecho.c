#include <stdio.h>

int main(int argc, char** argv, char** envp){
    char** p;
    int i = 0;

    printf("Command-line arguments:\n");
    p = argv;
    while(*p != NULL){
        printf("argv[%2d]: %s\n", i, *p);
        p++;
        i++;
    }

    printf("Environment variables:\n");
    p = envp;
    i = 0;
    while(*p != NULL){
        printf("envp[%2d]: %s\n", i, *p);
        p++;
        i++;
    }

    return 0;
}