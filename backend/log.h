#ifndef _LOG_H_
#define _LOG_H_

#include "test.h"

typedef struct 
{
	uint64_t execution_time[NUM_ITERATIONS];
	uint64_t miss_count[NUM_ITERATIONS];
	uint64_t load_count[NUM_ITERATIONS];
	uint64_t store_count[NUM_ITERATIONS];
	uint64_t cacheline_in[NUM_ITERATIONS];
	uint64_t cacheline_out[NUM_ITERATIONS];
	uint64_t minstret[NUM_ITERATIONS];
	
}log_t;



void log_display(uint64_t* num_shared_var,uint64_t* num_private_var,uint64_t* private_in_shared,uint64_t* private_first_write);
void log_update(int num_shared_var);

#endif
