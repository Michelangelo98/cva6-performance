#include "io.h"
#include "counter.h"
#include "arch.h"
#include "test.h"
#include "rand.h"

static counter_t counter;


inline void delay(int n)
{
  for (int i = 0; i < n; i++)
    asm volatile ("nop\n");
}


void counter_init()
{
	/*counter.counter = 0;

	counter.lock = 0;*/
}

void counter_print(){
    put_string("Shared counter, #iterations = ");
    put_uint32(COUNTER_ITERATIONS);
}

void counter_op(int pid)
{
	//uint32_t seed = 1212 + pid;
	for (int i = 0; i < COUNTER_ITERATIONS; ++i)
	{	
		//delay(rand_k(&(seed),500));
		for (int i = 0; i < N_VARIABLES; ++i)
		{
			counter.counter[4*i]++;
		}
		acquire(&counter.lock);
		for (int i = 0; i < N_VARIABLES; ++i)
		{
			counter.counter[4*i]++;
		}
		release(&counter.lock);
	}
}

int counter_check()
{
	/*if(counter.counter != COUNTER_ITERATIONS*NUM_PROCESSES)
	{
		return -1;
	}*/
	return 0;
}