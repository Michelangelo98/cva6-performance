#ifndef _TEST_H_
#define _TEST_H_

#include <stdint.h>

// ==========
// Parameters 
// ==========

#define MAX_VECTOR_SIZE 10000
#define NUM_ITERATIONS 18
#define NUM_PROCESSES  2
#define NUM_PRIVATE_VAR { 5000,5000,5000,5000,5000,5000,5000,5000,5000 ,5000 ,500  ,500  ,50   ,50   ,5     ,5   ,1    ,1 }//,100,1,100,10000,10000,10000 }
#define NUM_SHARED_VAR  { 1   ,1   ,10  ,10  ,100 ,100 ,1000,1000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000 }
//#define NUM_PRIVATE_VAR { 5000,5000,5000,5000,5000,5000,5000,5000,5000,5000,500,500,50,50,5,5,1,1 }
//#define NUM_SHARED_VAR { 1,1,10,10,100,100,1000,1000,10000,10000,10000,10000,10000,10000,10000,10000,10000,10000 }
#define PRIVATE_IN_SHARED { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 }//,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }//,0,0,0,0,0,0 } 
#define PRIVATE_FIRST_WRITE { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 } //,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }//,100/2,1,100/2,10000/2,10000/2,10000/2 }


// =====
// Types
// =====

// Shared variables in litmus test
typedef int32_t var_t;

typedef struct {
  // Shared variables
  volatile var_t     outcome[MAX_VECTOR_SIZE];

  // Private variables
  var_t private_vect[MAX_VECTOR_SIZE];

  // CS lock
  volatile uint32_t   lock;

  volatile uint64_t start_time[NUM_PROCESSES];

  volatile uint64_t end_time;

  volatile uint64_t start_minstret[NUM_PROCESSES];

  volatile uint64_t end_minstret[NUM_PROCESSES];

  volatile uint64_t start_miss[NUM_PROCESSES];

  volatile uint64_t end_miss[NUM_PROCESSES];

  volatile uint64_t start_load[NUM_PROCESSES];

  volatile uint64_t end_load[NUM_PROCESSES];

  volatile uint64_t start_store[NUM_PROCESSES];

  volatile uint64_t end_store[NUM_PROCESSES];

  volatile uint64_t start_cacheline_in[NUM_PROCESSES];

  volatile uint64_t end_cacheline_in[NUM_PROCESSES];

  volatile uint64_t start_cacheline_out[NUM_PROCESSES];

  volatile uint64_t end_cacheline_out[NUM_PROCESSES];

} test_t;


// =========
// Functions
// =========

void test_init();
void test_body(int pid,int num_shared_var,int num_private_var,int private_in_shared,int private_first_write);

#endif
