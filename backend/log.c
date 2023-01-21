#include <stdint.h>
#include "log.h"
#include "io.h"
#include "test.h"

extern test_t test;

int log_check_coherence()
{
  for (int i = 0; i < VECTOR_SIZE; i++)
  {
    if (test.outcome[i] != NUM_PROCESSES*NUM_ITERATIONS)
    {
      return -1;
    }
  }
  return 0;
}

void log_print_performance()
{
  put_string("Start time: ");
  put_uint64(test.start_time);
  put_string("\n");

  put_string("End time: ");
  put_uint64(test.end_time);
  put_string("\n");

  put_string("Execution time: ");
  put_uint64(test.end_time - test.start_time);
  put_string("\n");

  put_string("Miss count (core 0): ");
  put_uint64(test.end_miss[0] - test.start_miss[0]);
  put_string("\n");

  put_string("Miss count (core 1): ");
  put_uint64(test.end_miss[1] - test.start_miss[1]);
  put_string("\n");

  put_string("Store count (core 0): ");
  put_uint64(test.end_store[0] - test.start_store[0]);
  put_string("\n");

  put_string("Store count (core 1): ");
  put_uint64(test.end_store[1] - test.start_store[1]);
  put_string("\n");

  put_string("Load count (core 0): ");
  put_uint64(test.end_load[0] - test.start_load[0]);
  put_string("\n");

  put_string("Load count (core 1): ");
  put_uint64(test.end_load[1] - test.start_load[1]);
  put_string("\n");

  put_string("WB count (core 0): ");
  put_uint64(test.end_cacheline_in[0] - test.start_cacheline_in[0]);
  put_string("\n");

  put_string("WB count (core 1): ");
  put_uint64(test.end_cacheline_in[1] - test.start_cacheline_in[1]);
  put_string("\n");

  put_string("Cacheline loaded (core 0): ");
  put_uint64(test.end_cacheline_out[0] - test.start_cacheline_out[0]);
  put_string("\n");

  put_string("Cacheline loaded (core 1): ");
  put_uint64(test.end_cacheline_out[1] - test.start_cacheline_out[1]);
  put_string("\n");

}
void log_display()
{
  put_string("log_display started\r\n");
  /*if(log_check_coherence() == -1){
    put_string("ERROR: coherence not ensured\r\n");
  }
  else{*/
    log_print_performance();
  //}
}
