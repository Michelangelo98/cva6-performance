#ifndef _ARCH_H_
#define _ARCH_H_

#include <stdint.h>

#define CSR_MLOAD           0xB07
#define CSR_MSTORE          0xB08
#define CSR_ML1_DCACHE_MISS 0xB04
#define CSR_CACHELINE_IN    0xB11
#define CSR_CACHELINE_OUT   0xB12
#define CSR_MCYCLE          0xB00

#define STRINGIZE1(x) #x
#define STRINGIZE(x) STRINGIZE1(x)

// Interface to CPU architecture specific code

void arch_barrier_up();
void arch_barrier_down();
void arch_generic_barrier();

void acquire(volatile uint32_t * lock);
void release(volatile uint32_t * lock);


uint64_t arch_get_process_id();
uint64_t arch_get_counter();
uint64_t arch_get_miss();
uint64_t arch_get_load();
uint64_t arch_get_store();
uint64_t arch_get_cacheline_in();
uint64_t arch_get_cacheline_out();
uint64_t arch_get_minstret();
uint64_t arch_get_inv();
uint64_t arch_get_wb_inv();
uint64_t arch_get_miss_tot();
uint64_t arch_get_amo();

#endif
