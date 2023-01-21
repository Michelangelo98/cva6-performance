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

/*  // Random seed
  uint32_t seed = 14593;*/

  // Processes not being used spin here
  if (me >= NUM_PROCESSES) while (1);

  if (me == 0) {
    init_uart(50000000, 115200*4);
    put_string("Hello World!\n");
    test_init();
  }

  test_body(me);

  if (me == 0) {
    log_display();
    put_string("Time\n");
  }

  return 0;
}
