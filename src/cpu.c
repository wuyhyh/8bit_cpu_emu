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

		printf("[PC=0x%02X] Executing opcode: 0x%02X\n", cpu->pc,
		       instr);

		switch (instr) {
		case INSTR_NOP:
			cpu->pc += 1;
			break;

		case INSTR_HALT:
			printf("HALT encountered. Stopping CPU.\n");
			return;

		case INSTR_LOAD_IMM: {
			u8 reg = memory_read(cpu->mem, cpu->pc + 1);
			u8 val = memory_read(cpu->mem, cpu->pc + 2);

			if (reg >= 4)
				panic("Invalid register in LOAD");

			cpu->regs[reg] = val;
			cpu->zf = (val == 0);
			cpu->pc += 3;
			break;
		}

		case INSTR_MOV: {
			u8 dst = memory_read(cpu->mem, cpu->pc + 1);
			u8 src = memory_read(cpu->mem, cpu->pc + 2);

			if (dst >= 4 || src >= 4)
				panic("Invalid register in MOV");

			cpu->regs[dst] = cpu->regs[src];
			cpu->zf = (cpu->regs[dst] == 0);
			cpu->pc += 3;
			break;
		}

		case INSTR_LOADM: {
			u8 reg = memory_read(cpu->mem, cpu->pc + 1);
			u8 addr = memory_read(cpu->mem, cpu->pc + 2);

			if (reg >= 4)
				panic("Invalid register in LOADM");

			cpu->regs[reg] = memory_read(cpu->mem, addr);
			cpu->zf = (cpu->regs[reg] == 0);
			cpu->pc += 3;
			break;
		}

		case INSTR_STORE: {
			u8 reg = memory_read(cpu->mem, cpu->pc + 1);
			u8 addr = memory_read(cpu->mem, cpu->pc + 2);

			if (reg >= 4)
				panic("Invalid register in STORE");

			memory_write(cpu->mem, addr, cpu->regs[reg]);
			cpu->pc += 3;
			break;
		}

		case INSTR_ADD: {
			u8 dst = memory_read(cpu->mem, cpu->pc + 1);
			u8 src = memory_read(cpu->mem, cpu->pc + 2);

			if (dst >= 4 || src >= 4)
				panic("Invalid register in ADD");

			u8 result = alu_add(&cpu->alu, cpu, cpu->regs[dst],
					    cpu->regs[src]);
			cpu->regs[dst] = result;
			cpu->pc += 3;
			break;
		}

		default:
			printf("Unknown instruction: 0x%02X\n", instr);
			panic("Invalid instruction");
		}

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
