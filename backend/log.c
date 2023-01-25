#include <stdint.h>
#include "log.h"
#include "io.h"
#include "test.h"

extern test_t test;
static log_t log;

int log_check_coherence(int num_shared_var)
{
  for (int i = 0; i < num_shared_var; i++)
  {
    if (test.outcome[i] != NUM_PROCESSES*10)
    {
      put_string("Error for shared var at i = ");
      put_uint64((uint64_t)i);
      put_string("Error for shared var  = ");
      put_uint64((uint64_t)test.outcome[i]);
      put_string("\n");
      return -1;
    }
  }

  /*for (int j = 0; j < NUM_PROCESSES; j++)
  {
    for (int i = 0; i < NUM_PRIVATE_VAR; i++)
    {
      if (test.private_vect[i][j] != NUM_CS*NUM_PRIVATE_ACCESSES)
      {
        put_string("Error for private var at var,pid = ");
        put_uint64((uint64_t)i);
        put_uint64((uint64_t)j);
        put_string("\n");
        return -1;
      }
    }
  }*/
  
  return 0;
}

void log_update(int num_shared_var) 
{
  static int i = 0;

  //put_string("log_update\n");

  log.execution_time[i] = test.end_time - (test.start_time[0]+test.start_time[1])/2;

  log.miss_count[i] = test.end_miss[0] - test.start_miss[0];
  log.load_count[i] = test.end_load[0] - test.start_load[0];
  log.store_count[i] = test.end_store[0] - test.start_store[0];
  log.cacheline_in[i] = test.end_cacheline_in[0] - test.start_cacheline_in[0];
  log.cacheline_out[i] = test.end_cacheline_out[0] - test.start_cacheline_out[0];
  log.minstret[i] = ((test.end_minstret[0]+test.end_minstret[1]) - (test.start_minstret[0]+test.start_minstret[1]))/2;

  if(log_check_coherence(num_shared_var) == -1){
    put_string("ERROR: coherence not ensured\r\n");
  }
  i++;

}

void log_print_stat(uint64_t* stat)
{
  for (int i = 0; i < NUM_ITERATIONS; i++)
  {
    put_uint64(stat[i]);
    put_string("  ");
  }
}



void log_print_performance(uint64_t* num_shared_var,uint64_t* num_private_var,uint64_t* private_in_shared,uint64_t* private_first_write)
{
  /*put_string("Start time: ");
  put_uint64(test.start_time);
  put_string("\n");

  put_string("End time: ");
  put_uint64(test.end_time);
  put_string("\n");*/

  put_string("NUM_SHARED_VAR: ");
  log_print_stat(num_shared_var);
  put_string("\n");

  put_string("NUM_PRIVATE_VAR: ");
  log_print_stat(num_private_var);
  put_string("\n");

  put_string("PRIVATE_IN_SHARED: ");
  log_print_stat(private_in_shared);
  put_string("\n");

  put_string("PRIVATE_FIRST_WRITE: ");
  log_print_stat(private_first_write);
  put_string("\n");

  put_string("----------\n");

  put_string("Cycles: ");
  log_print_stat(&log.execution_time[0]);
  put_string("\n");

  put_string("Retired instructions: ");
  log_print_stat(&log.minstret[0]);
  put_string("\n");


  put_string("Miss count (core 0): ");
  log_print_stat(&log.miss_count[0]);
  put_string("\n");

/*  put_string("Miss count (core 1): ");
  log_print_stat(test.end_miss[1] - test.start_miss[1]);
  put_string("\n");
*/
  put_string("Store count (core 0): ");
  log_print_stat(&log.store_count[0]);
  put_string("\n");

/*  put_string("Store count (core 1): ");
  log_print_stat(test.end_store[1] - test.start_store[1]);
  put_string("\n");
*/
  put_string("Load count (core 0): ");
  log_print_stat(&log.load_count[0]);
  put_string("\n");

/*  put_string("Load count (core 1): ");
  log_print_stat(test.end_load[1] - test.start_load[1]);
  put_string("\n");*/

  put_string("WB count (core 0): ");
  log_print_stat(&log.cacheline_out[0]);
  put_string("\n");

/*  put_string("WB count (core 1): ");
  log_print_stat(test.end_cacheline_in[1] - test.start_cacheline_in[1]);
  put_string("\n");*/

  put_string("Cacheline loaded (core 0): ");
  log_print_stat(&log.cacheline_in[0]);
  put_string("\n");

/*  put_string("Cacheline loaded (core 1): ");
  log_print_stat(test.end_cacheline_out[1] - test.start_cacheline_out[1]);
  put_string("\n");*/

}
void log_display(uint64_t* num_shared_var,uint64_t* num_private_var,uint64_t* private_in_shared,uint64_t* private_first_write)
{
  //put_string("log_display started\r\n");
  log_print_performance(num_shared_var,num_private_var,private_in_shared,private_first_write);
}
