#ifndef _TEST_H_
#define _TEST_H_

#include <stdint.h>

// ==========
// Parameters 
// ==========

#define NUM_PROCESSES 2
#define NUM_ITERATIONS 2
#define VECTOR_SIZE 5
#define NUM_SHARED_ACCESSES 2

// =====
// Types
// =====

// Shared variables in litmus test
typedef int32_t var_t;

typedef struct {
  // The outcome vector
  volatile var_t     outcome[VECTOR_SIZE];

  // For logging the start time of a test on each process
  volatile uint32_t   lock;

  uint64_t start_time;

  uint64_t end_time;

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
void test_body(int pid);

#endif
