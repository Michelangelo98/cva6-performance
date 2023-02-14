#ifndef _RAND_READ_WRITE_
#define _RAND_READ_WRITE_

#include <stdint.h>
#include "test.h"

// ==========
// Parameters 
// ==========

#define NUM_ITERATIONS 10
#define MAX_PRIV 100
#define MAX_SHARE 100


typedef struct {

  volatile uint32_t priv_vect[MAX_PRIV][NUM_PROCESSES];

  volatile uint32_t share_vect[MAX_PRIV];

  volatile uint32_t lock;

} rand_rw_t;

void rand_rw_op(int pid);

int rand_rw_check();

void rand_rw_init();

void rand_rw_print();

#endif
