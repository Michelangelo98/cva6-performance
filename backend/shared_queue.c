#include "io.h"
#include "shared_queue.h"
#include "arch.h"
#include "test.h"
#include "rand.h"
#include <stddef.h>


struct Queue q;

int32_t outcomes[MAX_NODES];


inline void delay(int n)
{
  for (int i = 0; i < n; i++)
    asm volatile ("nop\n");
}


// Initialize the queue
void initQueue() {
    q.head = 0;
    q.tail = 0;
}

// Add an element to the queue
void enqueue(int32_t data) {

    static int node_index = 0;

    //struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    nodes[node_index].data = data;
    nodes[node_index].next = NULL;

    acquire(&q.lock);
    if (q.tail == NULL) {
        // The queue is empty
        q.head = &nodes[node_index];
        q.tail = &nodes[node_index];
    } else {
        // Add the new node to the end of the list
        q.tail->next = &nodes[node_index];
        q.tail = &nodes[node_index];
    }
    node_index += 4;
    release(&q.lock);
}

// Remove an element from the queue
int32_t dequeue() {
    acquire(&q.lock);
    if (q.head == NULL) {
        // The queue is empty
        release(&q.lock);
        return -1;
    } else {
        struct Node *temp = q.head;
        int32_t data = temp->data;
        q.head = temp->next;

        if (q.head == NULL) {
            // The queue is now empty
            q.tail = NULL;
        }
        release(&q.lock);
        return data;
    }
}

void shared_queue_init(){
    initQueue();
}

void shared_queue_print(){
    put_string("Shared queue, #iterations = ");
    put_uint32(MAX_NODES);
}

int shared_queue_check(){
    
    int32_t expected_value = 0;

    for (int i = 0; i < MAX_NODES; ++i)
    {
        if (outcomes[i] == expected_value) 
        {
            expected_value++;
        }else if (outcomes[i] != -1)
        {
            return -1;
        }
    }

    return 0;
}

void shared_queue_op(int pid){

    uint32_t seed = 1212 + pid;
    for (int i = 0; i < MAX_NODES; ++i)
    {
        delay(rand_k(&(seed),500));
        if (pid == 0)
        {   
            outcomes[i] = dequeue();
        }else if (pid == 1)
        {
            enqueue(i);
        }
    }
}
