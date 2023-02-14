#ifndef _TEST_H_
#define _TEST_H_

#include <stdint.h>

// ==========
// Parameters 
// ==========


#define NUM_PROCESSES  2


// =====
// Types
// =====



typedef struct {

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

  volatile uint64_t end_inv[NUM_PROCESSES];

  volatile uint64_t end_wb_inv[NUM_PROCESSES];

  volatile uint64_t end_miss_tot[NUM_PROCESSES];

  volatile uint64_t end_amo[NUM_PROCESSES];

  volatile uint64_t start_inv[NUM_PROCESSES];

  volatile uint64_t start_wb_inv[NUM_PROCESSES];

  volatile uint64_t start_miss_tot[NUM_PROCESSES];

  volatile uint64_t start_amo[NUM_PROCESSES];

} monitors_t;


// =========
// Functions
// =========

void test_init();

void test_body(int pid);

int test_check_coherence();

void test_print();

#endif
