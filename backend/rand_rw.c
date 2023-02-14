#include "io.h"
#include "rand_rw.h"
#include "arch.h"
#include "test.h"
#include "rand.h"

static rand_rw_t rand_rw;


void rand_rw_init()
{
	rand_rw.lock = 0;
}

void rand_rw_print(){
    put_string("Random RW, #iterations = ");
    put_uint32(NUM_ITERATIONS);
    put_string(" vectors size = ");
    put_uint32(MAX_PRIV);
}


void rand_rw_op(int pid)
{
	uint32_t seed = 1212 + pid;
	uint32_t rand_tmp;
	volatile uint32_t read_tmp;

	for (int i = 0; i < NUM_ITERATIONS; ++i)
	{	
		//private random read
		rand_tmp = rand_k(&(seed),MAX_PRIV);
		for (int i = 0; i < rand_tmp; ++i)
		{
			read_tmp = rand_rw.priv_vect[rand_k(&(seed),MAX_PRIV/2)*2][pid];
		}
		//private random write
		rand_tmp = rand_k(&(seed),MAX_PRIV);
		for (int i = 0; i < rand_tmp; ++i)
		{
			rand_rw.priv_vect[rand_k(&(seed),MAX_PRIV/2)*2][pid] = i;
		}
		//shared random read
		/*rand_tmp = rand_k(&(seed),MAX_SHARE);
		for (int i = 0; i < rand_tmp; ++i)
		{
			read_tmp = rand_rw.share_vect[rand_k(&(seed),MAX_SHARE/4)*4];
		}*/

		acquire(&rand_rw.lock);
		//private random read
		rand_tmp = rand_k(&(seed),MAX_PRIV);
		for (int i = 0; i < rand_tmp; ++i)
		{
			read_tmp = rand_rw.priv_vect[rand_k(&(seed),MAX_PRIV/2)*2][pid];
		}
		//private random write
		rand_tmp = rand_k(&(seed),MAX_PRIV);
		for (int i = 0; i < rand_tmp; ++i)
		{
			rand_rw.priv_vect[rand_k(&(seed),MAX_PRIV/2)*2][pid] = i;
		}
		//shared random read
		rand_tmp = rand_k(&(seed),MAX_SHARE);
		for (int i = 0; i < rand_tmp; ++i)
		{
			read_tmp = rand_rw.share_vect[rand_k(&(seed),MAX_SHARE/4)*4];
		}
		//shared random write
		rand_tmp = rand_k(&(seed),MAX_SHARE);
		for (int i = 0; i < rand_tmp; ++i)
		{
			rand_rw.share_vect[rand_k(&(seed),MAX_SHARE/4)*4] = i;
		}
		release(&rand_rw.lock);
	}

	//dummy read to avoid warning
	read_tmp++;
}

int rand_rw_check()
{
	return 0;
}