#include "io.h"
#include "test.h"
#include "arch.h"
#include "rand.h"



#if defined COUNTER
    #include "counter.h"
#elif defined RAND_RW
    #include "rand_rw.h"
#else
    #include "shared_queue.h"
#endif


// ================
// Global variables
// ================

monitors_t monitors;

// =========
// Functions
// =========

int test_check_coherence()
{
  //put_string("test_init started\r\n");

  #if defined COUNTER
    return counter_check();
  #elif defined RAND_RW
    return rand_rw_check();
  #else
    return shared_queue_check();
  #endif

}

void test_init()
{
  //put_string("test_init started\r\n");
  #if defined COUNTER
    counter_init();
  #elif defined RAND_RW
    rand_rw_init();
  #else
    shared_queue_init();
  #endif

}


void test_print()
{
  //put_string("test_init started\r\n");
  #if defined COUNTER
    counter_print();
  #elif defined RAND_RW
    rand_rw_print();
  #else
    shared_queue_print();
  #endif

}


void test_body(int pid) {

  //sync start of test
  arch_barrier_up();
/*  //save stat
  monitors.start_miss[pid] = arch_get_miss();
  monitors.start_load[pid] = arch_get_load();
  monitors.start_store[pid] = arch_get_store();
  monitors.start_cacheline_in[pid]  = arch_get_cacheline_in();
  monitors.start_cacheline_out[pid] = arch_get_cacheline_out();
  monitors.start_inv[pid] = arch_get_inv();
  monitors.start_wb_inv[pid] = arch_get_wb_inv();
  monitors.start_miss_tot[pid] = arch_get_miss_tot();
  monitors.start_amo[pid] = arch_get_amo();
  monitors.start_minstret[pid] = arch_get_minstret();
  //start performance counter
  monitors.start_time[pid] = arch_get_counter();*/

#if defined COUNTER
  counter_op(pid);
#elif defined RAND_RW
  rand_rw_op(pid);
#else
  shared_queue_op(pid);
#endif




  //sync end of test
  arch_barrier_down();

  /*monitors.end_miss[pid] = arch_get_miss();
  monitors.end_load[pid] = arch_get_load();
  monitors.end_store[pid] = arch_get_store();
  monitors.end_cacheline_in[pid]  = arch_get_cacheline_in();
  monitors.end_cacheline_out[pid] = arch_get_cacheline_out();
  monitors.end_inv[pid] = arch_get_inv();
  monitors.end_wb_inv[pid] = arch_get_wb_inv();
  monitors.end_miss_tot[pid] = arch_get_miss_tot();
  monitors.end_amo[pid] = arch_get_amo();
  monitors.end_minstret[pid] = arch_get_minstret();
  monitors.end_time = arch_get_counter(); */   

  
}
