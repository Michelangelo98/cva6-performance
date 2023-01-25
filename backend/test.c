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

void test_init(int num_shared_var,int num_private_var)
{
  //put_string("test_init started\r\n");

  test.lock = 0;
  for (int i = 0; i < num_shared_var; i++)
  {
    test.outcome[i] = 0;
  }
  /*for (int i = 0; i < NUM_PROCESSES; i++)
  {*/
    for (int j = 0; j < num_private_var; j++)
    {
      test.private_vect[j]=0;
    }
  /*}*/

}


inline void delay(int n)
{
  for (int i = 0; i < n; i++)
    asm volatile ("nop\n");
}


void test_op(int pid,int num_shared_var,int num_private_var,int private_in_shared,int private_first_write)
{
  
    /* pre-code */
    // operations on private vars (read -> write)
    for (int i = 0; i < num_private_var; i++)
    {
      for (int j = 0; j < 10; j++)
      {
        test.private_vect[i]++;
      }      
            
    }
    
    acquire(&test.lock);

    /* Critical section */
    // operations on private vars - no need to be invalidated
    /*for (int i = 0; i < private_in_shared; i++)
    {      
      test.private_vect[i]++;      
    }*/
    // operations on shared vars - they must be taken from main memory
    for (int i = 0; i < num_shared_var; i++)
    {          

      for (int j = 0; j < 10; j++)
      {
        test.outcome[i]++;
      }

    }
    release(&test.lock);

    /* post-code */

    // operations on private vars (write), never evicted from the cache
    // for sync operations
    /*for (int i = 0; i < private_first_write; i++)
    {
      test.private_vect[i] = i;
    }*/

    // operations on private vars (read -> write)
    for (int i = 0; i < num_private_var; i++)
    {
      for (int j = 0; j < 10; j++)
      {
        test.private_vect[i]++;
      }
    }

    
      
}

void test_body(int pid,int num_shared_var,int num_private_var,int private_in_shared,int private_first_write) {

  //sync start of test
  arch_barrier_up();
  //save stat
  test.start_miss[pid] = arch_get_miss();
  test.start_load[pid] = arch_get_load();
  test.start_store[pid] = arch_get_store();
  test.start_cacheline_in[pid]  = arch_get_cacheline_in();
  test.start_cacheline_out[pid] = arch_get_cacheline_out();
  test.start_minstret[pid] = arch_get_minstret();

  switch(pid) {
    case 0: {

      //start performance counter
      test.start_time[pid] = arch_get_counter();


      test_op(pid,num_shared_var,num_private_var, private_in_shared, private_first_write);

      test.end_minstret[pid] = arch_get_minstret();
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
      test.start_time[pid] = arch_get_counter();
      
      test_op(pid,num_shared_var,num_private_var, private_in_shared, private_first_write);

      test.end_minstret[pid] = arch_get_minstret();
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
