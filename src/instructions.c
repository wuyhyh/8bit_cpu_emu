#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memory.h"
#include "util.h"
#include "instructions.h"

instr_fn_t instruction_table[256] = { 0 };

/* ---------- 指令实现 ---------- */

static void instr_nop(struct cpu *cpu)
{
	cpu->pc += 1;
}

static void instr_halt(struct cpu *cpu)
{
	printf("HALT encountered. Stopping CPU.\n");
	exit(0);
}

static void instr_load_imm(struct cpu *cpu)
{
	u8 reg = memory_read(cpu->mem, cpu->pc + 1);
	u8 val = memory_read(cpu->mem, cpu->pc + 2);

	if (reg >= 4)
		panic("Invalid register in LOAD");

	cpu->regs[reg] = val;
	cpu->zf = (val == 0);
	cpu->pc += 3;
}

/* ---------- 注册表初始化 ---------- */

void instructions_init(void)
{
	instruction_table[0x00] = instr_nop;
	instruction_table[0xFF] = instr_halt;
	instruction_table[0x10] = instr_load_imm;

	/* 后续支持：instruction_table[0x11] = instr_mov; ... */
}
