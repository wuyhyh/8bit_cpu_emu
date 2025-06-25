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

#include "instructions.h"

void cpu_run(struct cpu *cpu)
{
	while (1) {
		u8 opcode = memory_read(cpu->mem, cpu->pc);
		instr_fn_t fn = instruction_table[opcode];

		printf("[PC=0x%02X] Executing opcode: 0x%02X\n", cpu->pc,
		       opcode);

		if (!fn) {
			printf("Unknown instruction: 0x%02X\n", opcode);
			panic("Invalid instruction");
		}

		fn(cpu); /* 调用对应指令处理函数 */

#ifdef ENABLE_DUMP
		cpu_dump_state(cpu);
#endif
	}
}

void cpu_dump_state(struct cpu *cpu)
{
	printf("PC=%02X | ", cpu->pc);
	printf("R0=%02X R1=%02X R2=%02X R3=%02X | ", cpu->regs[0], cpu->regs[1],
	       cpu->regs[2], cpu->regs[3]);
	printf("ZF=%d CF=%d | ", cpu->zf, cpu->cf);
	printf("ALU=%02X\n", cpu->alu.last_result);
}
