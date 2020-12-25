#include "csapp.h"

sem_t mutex;
#define LINESIZE 25

char *ctime_ts(const time_t *timep, char *privatep);

int main(){
    time_t t;
    char p[LINESIZE];
    /* get time of now */
    /* take an output argument time_t *t */
    /* Returns: time_t */
    time(&t);

    Sem_init(&mutex, 0, 1);

    printf("%s", ctime_ts(&t, p));
    return 0;
}

char *ctime_ts(const time_t *timep, char *privatep)
{
    char *sharedp;

    P(&mutex);
    sharedp = ctime(timep);
    strcpy(privatep, sharedp); /* Copy string from shared to private */
    V(&mutex);
    return privatep;
}