#include <stdio.h>
#include "cpu.h"
#include "util.h"
#include "instructions.h"

void cpu_init(struct cpu *cpu, struct memory *mem)
{
	int i;

	for (i = 0; i < 4; i++)
		cpu->regs[i] = 0;

	cpu->pc = 0;
	cpu->zf = 0;
	cpu->cf = 0;
	cpu->mem = mem;

	/* 初始化 ALU 内部状态 */
	cpu->alu.last_result = 0;
	cpu->alu.carry = 0;
}

void cpu_run(struct cpu *cpu)
{
	while (1) {
		u8 instr = memory_read(cpu->mem, cpu->pc);

		printf("[PC=0x%02X] Executing opcode: 0x%02X\n", cpu->pc, instr);

		switch (instr) {
		case INSTR_NOP:
			cpu->pc += 1;
			break;
		case INSTR_HALT:
			printf("HALT encountered. Stopping CPU.\n");
			return;
		default:
			printf("Unknown instruction: 0x%02X\n", instr);
			panic("Invalid instruction");
		}
	}
}
