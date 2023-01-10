#include "benchmarkussswLib.h"

#include <stdint.h>
#include <string.h>

#if ENABLE_USS_LIB_BENCHMARK

/* Generic function entry, record benchmark and push new pointer */
void BENCHMARK_ENTRY_USS_LIB(void)
{
    USS_BENCHMARK_PORT ^= (USS_BENCHMARK_PIN);
}

/* Generic function exit, record benchmark and pop last pointer */
void BENCHMARK_EXIT_USS_LIB(void)
{
    USS_BENCHMARK_PORT &= ~(USS_BENCHMARK_PIN);
}

#endif
