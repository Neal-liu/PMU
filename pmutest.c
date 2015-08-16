#include <stdio.h>
#include <stdint.h>


void init_pmu()
{

	/* Enable counters in Control Register and reset cycle count and event count */
	asm volatile("mcr   p15, 0, %0, c9, c12, 0" : : "r"(0x00000007));

	/* Event counter selection register, which counter to access */
	asm volatile("mcr   p15, 0, %0, c9, c12, 5" : : "r"(0x0));

	/* selected event type to record, instructions executed */
	asm volatile("mcr   p15, 0, %0, c9, c13, 1" : : "r"(0x00000008));

	/* count enable set register, bit 31 enables the cycle counter, 
	   and bit 0 enables the first counter */
	asm volatile("mcr   p15, 0, %0, c9, c12, 1" : : "r"(0x8000000f));

}

uint32_t read_cycles()
{
	uint32_t cycle_count;

	asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(cycle_count));

	return cycle_count;
}

uint32_t read_instructions()
{
	uint32_t instr_count;

	/* Event counter selection register, which counter to access */
	asm volatile("mcr   p15, 0, %0, c9, c12, 5" : : "r"(0x0));

	/* Read the instruction count */
	asm volatile("mrc p15, 0, %0, c9, c13, 2" : "=r"(instr_count));

	return instr_count;

}

main(int argc, char **argv)
{
	uint32_t  start=0, end=0;
	uint32_t  istart=0, iend=0;

	(void) init_pmu();

	start = read_cycles();
	istart = read_instructions();

	printf("Measuring cycle and instruction count for this printf\n");

	end = read_cycles();
	iend = read_instructions();

	printf("cycles %d instructions %d\n",end-start,iend-istart);

}
