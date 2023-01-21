#include "io.h"
#include "test.h"
#include "arch.h"
#include "rand.h"

// ================
// Global variables
// ================

test_t test;

// =========
// Functions
// =========

void test_init()
{
  put_string("test_init started\r\n");
  // Randomize variable locations
  test.lock = 0;
  for (int i = 0; i < VECTOR_SIZE; i++)
  {
    test.outcome[i] = 0;
  }

}


inline void delay(int n)
{
  for (int i = 0; i < n; i++)
    asm volatile ("nop\n");
}


void test_op()
{
  for (int i = 0; i < NUM_ITERATIONS; i++)
      {
        acquire(&test.lock);
        //Critical section
        for (int i = 0; i < VECTOR_SIZE; i++)
        {
          for (int i = 0; i < NUM_SHARED_ACCESSES; i++)
          {
            test.outcome[i]++;
          }
        }
        release(&test.lock);
      }
}

void test_body(int pid) {

  //sync start of test
  arch_barrier_up();
  //save stat
  test.start_miss[pid] = arch_get_miss();
  test.start_load[pid] = arch_get_load();
  test.start_store[pid] = arch_get_store();
  test.start_cacheline_in[pid]  = arch_get_cacheline_in();
  test.start_cacheline_out[pid] = arch_get_cacheline_out();

  switch(pid) {
    case 0: {

      //start performance counter
      test.start_time = arch_get_counter();


      test_op();

      test.end_miss[pid] = arch_get_miss();
      test.end_load[pid] = arch_get_load();
      test.end_store[pid] = arch_get_store();
      test.end_cacheline_in[pid]  = arch_get_cacheline_in();
      test.end_cacheline_out[pid] = arch_get_cacheline_out();


      //sync end of test
      arch_barrier_down();
      test.end_time = arch_get_counter();
      break;
    }
    case 1: {
      
      test_op();

      test.end_miss[pid] = arch_get_miss();
      test.end_load[pid] = arch_get_load();
      test.end_store[pid] = arch_get_store();
      test.end_cacheline_in[pid]  = arch_get_cacheline_in();
      test.end_cacheline_out[pid] = arch_get_cacheline_out();
      //sync end of test
      arch_barrier_down();
      break;
    }
  }

  
}
