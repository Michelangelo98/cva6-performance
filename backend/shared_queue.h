#ifndef _SHARED_QUEUE_
#define _SHARED_QUEUE_

#define MAX_NODES 1000


// Queue structure
struct Queue {
    int32_t array[MAX_NODES];
    uint32_t volatile head;
    uint32_t volatile tail;
};


void shared_queue_op(int pid);

int shared_queue_check();

void shared_queue_init();

void shared_queue_print();


#endif