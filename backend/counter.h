#ifndef _COUNTER_H_
#define _COUNTER_H_

#include <stdint.h>

#define COUNTER_ITERATIONS 10
#define N_VARIABLES 5000


typedef struct {

  volatile uint32_t counter[4*N_VARIABLES];

  volatile uint32_t lock;

} counter_t;

void counter_op(int pid);

int counter_check();

void counter_init();

void counter_print();


#endif
