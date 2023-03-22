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
int32_t enqueue(int32_t *data) {
    uint32_t current_tail = q.tail;
    if (current_tail == MAX_NODES) {
      return 1;
    }
    // Write data
    q.array[current_tail] = *data;
    arch_generic_barrier();
    // Safely update tail
    q.tail = current_tail+1;
    arch_generic_barrier();
    return 0;

}

// Remove an element from the queue
int32_t dequeue(int32_t *data) {
    arch_generic_barrier();
    uint32_t current_head = q.head;
    // Check if empty
    if (current_head == q.tail) {
      return 1;
    }
    // Read data
    *data = q.array[current_head];
    
    // Update head
    q.head = (current_head + 1);
    return 0;
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
        //put_int64((int64_t)outcomes[i]);
        //put_string(" ");
        if (outcomes[i] != expected_value) 
        {
            //put_string("ERROR ");
            return -1;
        }
        expected_value++;
    }

    return 0;
}

void shared_queue_op(int pid){

    //uint32_t seed = 1212 + pid;
    for (int i = 0; i < MAX_NODES; ++i)
    {
        //delay(rand_k(&(seed),500));
        if (pid == 0)
        {   
            int32_t ret;
            do{
                ret = dequeue(&outcomes[i]);
            }while(ret == 1);
            
        }else if (pid == 1)
        {
            enqueue(&i);      
        }
    }
}
