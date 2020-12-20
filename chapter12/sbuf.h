#ifndef _SBUF_H
#define _SBUF_H

#include <semaphore.h>

typedef struct {
    int *buf;       /* Buffer array */
    int n;          /* Maximum number of slots */
    int front;      /* buf[(front + 1)%n] is first item */
    int rear;       /* buf[rear%n] is last item */
    sem_t mutex;    /* Protects accesses to buf */
    sem_t slots;    /* Counts available slots */
    sem_t items;    /* Counts available items */
} sbuf_t;

/* Create an empty, bounded, shared FIFO buffer with n slots */
void sbuf_init(sbuf_t *sp, int n);

/* Clean up buffer sp */
void sbuf_deinit(sbuf_t *sp);

/* Insert itme onto the rear of shared buffer sp */
void sbuf_insert(sbuf_t *sp, int item);

/* Remove and return the first item from buffer sp */
int sbuf_remove(sbuf_t *sp);

#endif