#include <stdio.h>
#include "types.h"
#include "cpu.h"
#include "memory.h"
#include "util.h"

/* 示例程序：NOP, NOP, HALT */
static const u8 test_program[] = {
	0x00, // NOP
	0x00, // NOP
	0xFF  // HALT
};

int main(void)
{
	struct cpu cpu;
	struct memory mem;

	memory_init(&mem);
	memory_load(&mem, test_program, sizeof(test_program));

	cpu_init(&cpu, &mem);

	cpu_run(&cpu);

	return 0;
}
