#include "arch.h"
#include "rand.h"
#include "io.h"
#include "test.h"

// Code specific to RISCV64

// Hardware thread id =========================================================

uint64_t arch_get_process_id()
{
  uint64_t x;
  asm volatile("csrr %0, 0xf14" : "=r" (x));  //CSRRS rd, csr, x0
  return  x;
}

// Hardware counter ===========================================================

uint64_t arch_get_counter()
{
  uint64_t x;
  asm volatile("csrr %0, mcycle" : "=r" (x));
  return  x;
}

uint64_t arch_get_minstret()
{
  uint64_t x;
  asm volatile("csrr %0, minstret" : "=r" (x));
  return  x;
}

uint64_t arch_get_miss()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB04" : "=r" (x));
  return  x;
}

uint64_t arch_get_load()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB07" : "=r" (x));
  return  x;
}

uint64_t arch_get_store()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB08" : "=r" (x));
  return  x;
}

uint64_t arch_get_cacheline_in()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB11" : "=r" (x));
  return  x;
}

uint64_t arch_get_cacheline_out()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB12" : "=r" (x));
  return  x;
}

uint64_t arch_get_inv()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB13" : "=r" (x));
  return  x;
}

uint64_t arch_get_wb_inv()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB14" : "=r" (x));
  return  x;
}

uint64_t arch_get_miss_tot()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB15" : "=r" (x));
  return  x;
}

uint64_t arch_get_amo()
{
  uint64_t x;
  asm volatile("csrr %0, 0xB16" : "=r" (x));
  return  x;
}

// Barrier synchronisation ====================================================

// Shared variables
static volatile uint64_t barrier1 = 0;
static volatile uint64_t barrier2 = 0;

void barrier_wait(
    volatile uint64_t* barrier
  , uint64_t incr_amount
  , uint64_t reach
  )
{
  asm volatile (
      //"1:                                \n"
      //"lr.d   a0, 0(%0)                  \n"
      //"add    a0, a0, %1                 \n"
      //"sc.d   a0, a0, 0(%0)              \n"
      //"bnez   a0, 1b                     \n"
      "amoadd.d x6, %1, (%0)             \n"
      "2:                                \n"
      "fence                             \n"
      "ld     x6, 0(%0)                  \n"
      "bne    x6, %2, 2b                 \n"
      
  : /* output operands */
  : /* input operands */
    "r"(barrier),
    "r"(incr_amount),
    "r"(reach)
  : /* clobbered registers */
    "x6"
  );
}

void arch_barrier_up()
{
  barrier_wait(&barrier1, 1, NUM_PROCESSES);
  barrier_wait(&barrier2, 1, NUM_PROCESSES);
}

void arch_barrier_down()
{
  barrier_wait(&barrier1, -1, 0);
  barrier_wait(&barrier2, -1, 0);
}

void arch_generic_barrier()
{
  asm volatile (

      "nop                    \n"
      "fence                   \n"
      );
}

void acquire(volatile uint32_t * lock)
{
  asm volatile (

      "li t0,1                    \n"
      "again:                     \n"
      "amoswap.w.aq t0,t0, (%0)   \n"      
      "bnez t0, again             \n"
      
  : /* output operands */
  : /* input operands */
    "r"(lock));
}

void release(volatile uint32_t * lock)
{
  asm volatile (

      "nop                      \n"
      "amoswap.w.rl x0, x0, (%0)\n"
  : /* output operands */
  : /* input operands */
    "r"(lock));
}
