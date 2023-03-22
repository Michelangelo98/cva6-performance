#include <stdint.h>
#include "log.h"
#include "io.h"
#include "test.h"

extern monitors_t monitors;


void log_print_performance()
{


  put_string("Benchmark info: ");
  test_print();
  put_string("\n");


  put_string("Cycles: ");
  put_uint64(monitors.end_time - monitors.start_time[0]);
  put_string("\n");

  put_string("Retired instructions: ");
  put_uint64(monitors.end_minstret[0]-monitors.start_minstret[0]);
  put_string("\n");

  put_string("Inv time: ");
  put_uint64(monitors.end_inv[0] - monitors.start_inv[0]);
  put_string("\n");

  put_string("WB inv time: ");
  put_uint64(monitors.end_wb_inv[0] - monitors.start_wb_inv[0]);
  put_string("\n");

  put_string("Miss time: ");
  put_uint64(monitors.end_miss_tot[0] - monitors.start_miss_tot[0]);
  put_string("\n");

  put_string("Amo time: ");
  put_uint64(monitors.end_amo[0] - monitors.start_amo[0]);
  put_string("\n");

 /* put_string("Miss count (core 0): ");
  put_uint64(monitors.end_miss[0] - monitors.start_miss[0]);
  put_string("\n");

  put_string("Store count (core 0): ");
  put_uint64(monitors.end_store[0] - monitors.start_store[0]);
  put_string("\n");

  put_string("Load count (core 0): ");
  put_uint64(monitors.end_load[0] - monitors.start_load[0]);
  put_string("\n");

  put_string("WB count (core 0): ");
  put_uint64(monitors.end_cacheline_out[0] - monitors.start_cacheline_out[0]);
  put_string("\n");

  put_string("Cacheline loaded (core 0): ");
  put_uint64(monitors.end_cacheline_in[0] - monitors.start_cacheline_in[0]);
  put_string("\n");
*/

  /*ut_string("Miss count (core 1): ");
  put_uint64(monitors.end_miss[1] - monitors.start_miss[1]);
  put_string("\n");


  put_string("Store count (core 1): ");
  put_uint64(monitors.end_store[1] - monitors.start_store[1]);
  put_string("\n");



  put_string("Load count (core 1): ");
  put_uint64(monitors.end_load[1] - monitors.start_load[1]);
  put_string("\n");



  put_string("WB count (core 1): ");
  put_uint64(monitors.end_cacheline_in[1] - monitors.start_cacheline_in[1]);
  put_string("\n");

  put_string("Cacheline loaded (core 1): ");
  put_uint64(monitors.end_cacheline_out[1] - monitors.start_cacheline_out[1]);
  put_string("\n");*/

  

}

void log_display()
{
  //put_string("log_display started\r\n");
  if(test_check_coherence() == 0){
    //log_print_performance();
  }else{
    put_string("ERROR: coherence not ensured\r\n");
  }
  
}
