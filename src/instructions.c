#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "memory.h"
#include "alu.h"
#include "util.h"
#include "instructions.h"

instr_fn_t instruction_table[256] = { 0 };

/* -------------------- 指令函数实现 -------------------- */

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

static void instr_mov(struct cpu *cpu)
{
	u8 dst = memory_read(cpu->mem, cpu->pc + 1);
	u8 src = memory_read(cpu->mem, cpu->pc + 2);

	if (dst >= 4 || src >= 4)
		panic("Invalid register in MOV");

	cpu->regs[dst] = cpu->regs[src];
	cpu->zf = (cpu->regs[dst] == 0);
	cpu->pc += 3;
}

static void instr_add(struct cpu *cpu)
{
	u8 dst = memory_read(cpu->mem, cpu->pc + 1);
	u8 src = memory_read(cpu->mem, cpu->pc + 2);

	if (dst >= 4 || src >= 4)
		panic("Invalid register in ADD");

	cpu->regs[dst] =
		alu_add(&cpu->alu, cpu, cpu->regs[dst], cpu->regs[src]);
	cpu->pc += 3;
}

static void instr_sub(struct cpu *cpu)
{
	u8 dst = memory_read(cpu->mem, cpu->pc + 1);
	u8 src = memory_read(cpu->mem, cpu->pc + 2);

	if (dst >= 4 || src >= 4)
		panic("Invalid register in SUB");

	cpu->regs[dst] =
		alu_sub(&cpu->alu, cpu, cpu->regs[dst], cpu->regs[src]);
	cpu->pc += 3;
}

static void instr_inc(struct cpu *cpu)
{
	u8 reg = memory_read(cpu->mem, cpu->pc + 1);
	if (reg >= 4)
		panic("Invalid register in INC");

	cpu->regs[reg] = alu_add(&cpu->alu, cpu, cpu->regs[reg], 1);
	cpu->pc += 2;
}

static void instr_dec(struct cpu *cpu)
{
	u8 reg = memory_read(cpu->mem, cpu->pc + 1);
	if (reg >= 4)
		panic("Invalid register in DEC");

	cpu->regs[reg] = alu_sub(&cpu->alu, cpu, cpu->regs[reg], 1);
	cpu->pc += 2;
}

static void instr_loadm(struct cpu *cpu)
{
	u8 reg = memory_read(cpu->mem, cpu->pc + 1);
	u8 addr = memory_read(cpu->mem, cpu->pc + 2);

	if (reg >= 4)
		panic("Invalid register in LOADM");

	cpu->regs[reg] = memory_read(cpu->mem, addr);
	cpu->zf = (cpu->regs[reg] == 0);
	cpu->pc += 3;
}

static void instr_store(struct cpu *cpu)
{
	u8 reg = memory_read(cpu->mem, cpu->pc + 1);
	u8 addr = memory_read(cpu->mem, cpu->pc + 2);

	if (reg >= 4)
		panic("Invalid register in STORE");

	memory_write(cpu->mem, addr, cpu->regs[reg]);
	cpu->pc += 3;
}

static void instr_jmp(struct cpu *cpu)
{
	u8 addr = memory_read(cpu->mem, cpu->pc + 1);
	cpu->pc = addr;
}

static void instr_jz(struct cpu *cpu)
{
	u8 addr = memory_read(cpu->mem, cpu->pc + 1);
	cpu->pc = cpu->zf ? addr : cpu->pc + 2;
}

static void instr_jnz(struct cpu *cpu)
{
	u8 addr = memory_read(cpu->mem, cpu->pc + 1);
	cpu->pc = cpu->zf ? cpu->pc + 2 : addr;
}

static void instr_jc(struct cpu *cpu)
{
	u8 addr = memory_read(cpu->mem, cpu->pc + 1);
	cpu->pc = cpu->cf ? addr : cpu->pc + 2;
}

static void instr_jnc(struct cpu *cpu)
{
	u8 addr = memory_read(cpu->mem, cpu->pc + 1);
	cpu->pc = cpu->cf ? cpu->pc + 2 : addr;
}

static void instr_and(struct cpu *cpu)
{
	u8 dst = memory_read(cpu->mem, cpu->pc + 1);
	u8 src = memory_read(cpu->mem, cpu->pc + 2);
	if (dst >= 4 || src >= 4)
		panic("Invalid register in AND");

	cpu->regs[dst] &= cpu->regs[src];
	cpu->zf = (cpu->regs[dst] == 0);
	cpu->pc += 3;
}

static void instr_or(struct cpu *cpu)
{
	u8 dst = memory_read(cpu->mem, cpu->pc + 1);
	u8 src = memory_read(cpu->mem, cpu->pc + 2);
	if (dst >= 4 || src >= 4)
		panic("Invalid register in OR");

	cpu->regs[dst] |= cpu->regs[src];
	cpu->zf = (cpu->regs[dst] == 0);
	cpu->pc += 3;
}

static void instr_xor(struct cpu *cpu)
{
	u8 dst = memory_read(cpu->mem, cpu->pc + 1);
	u8 src = memory_read(cpu->mem, cpu->pc + 2);
	if (dst >= 4 || src >= 4)
		panic("Invalid register in XOR");

	cpu->regs[dst] ^= cpu->regs[src];
	cpu->zf = (cpu->regs[dst] == 0);
	cpu->pc += 3;
}

static void instr_not(struct cpu *cpu)
{
	u8 reg = memory_read(cpu->mem, cpu->pc + 1);
	if (reg >= 4)
		panic("Invalid register in NOT");

	cpu->regs[reg] = ~cpu->regs[reg];
	cpu->zf = (cpu->regs[reg] == 0);
	cpu->pc += 2;
}

/* -------------------- 注册所有指令 -------------------- */

void instructions_init(void)
{
	instruction_table[0x00] = instr_nop;
	instruction_table[0xFF] = instr_halt;
	instruction_table[0x10] = instr_load_imm;
	instruction_table[0x11] = instr_mov;
	instruction_table[0x12] = instr_loadm;
	instruction_table[0x13] = instr_store;
	instruction_table[0x20] = instr_add;
	instruction_table[0x21] = instr_sub;
	instruction_table[0x22] = instr_inc;
	instruction_table[0x23] = instr_dec;
	instruction_table[0x24] = instr_and;
	instruction_table[0x25] = instr_or;
	instruction_table[0x26] = instr_xor;
	instruction_table[0x27] = instr_not;
	instruction_table[0x30] = instr_jmp;
	instruction_table[0x31] = instr_jz;
	instruction_table[0x32] = instr_jnz;
	instruction_table[0x33] = instr_jc;
	instruction_table[0x34] = instr_jnc;
}
