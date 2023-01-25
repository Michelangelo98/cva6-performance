#include "io.h"
#include "log.h"
#include "platform.h"
#include "uart.h"
#include "arch.h"
#include "rand.h"
#include "test.h"

int main()
{
  // Get my global process id
  int me = arch_get_process_id();
  uint64_t num_shared_var[NUM_ITERATIONS] = NUM_SHARED_VAR;
  uint64_t num_private_var[NUM_ITERATIONS] = NUM_PRIVATE_VAR;
  uint64_t private_in_shared[NUM_ITERATIONS] = PRIVATE_IN_SHARED;
  uint64_t private_first_write[NUM_ITERATIONS] = PRIVATE_FIRST_WRITE;

/*  // Random seed
  uint32_t seed = 14593;*/

  // Processes not being used spin here
  if (me >= NUM_PROCESSES) while (1);

  if (me == 0) {
    init_uart(50000000, 115200*4);
    put_string("Hello World!\n");
    
  }

  for (int i = 0; i < NUM_ITERATIONS; i++)
  {
    if (me == 0) {
      test_init((int)num_shared_var[i],(int)num_private_var[i]);  
    }

    test_body(me,(int)num_shared_var[i],(int)num_private_var[i],(int)private_in_shared[i],(int)private_first_write[i]);

    if (me == 0) {
      log_update((int)num_shared_var[i]);
    }    
  }
  

  if (me == 0) {
    log_display(&num_shared_var[0],&num_private_var[0],&private_in_shared[0],&private_first_write[0]);
    put_string("Time\n");
  }

  return 0;
}
