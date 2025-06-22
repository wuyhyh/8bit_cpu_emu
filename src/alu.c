#include "alu.h"
#include "cpu.h"

/**
 * alu_add - 实现加法，带进位判断与 ZF 更新
 */
u8 alu_add(struct alu *alu, struct cpu *cpu, u8 a, u8 b)
{
	u8 result = a + b;
	alu->last_result = result;
	alu->carry = (result < a);  /* 检查是否进位 */

	cpu->zf = (result == 0);
	cpu->cf = alu->carry;

	return result;
}

/**
 * alu_sub - 实现减法，更新 ZF/CF
 */
u8 alu_sub(struct alu *alu, struct cpu *cpu, u8 a, u8 b)
{
	u8 result = a - b;
	alu->last_result = result;
	alu->carry = (a < b);  /* 借位时设置 carry */

	cpu->zf = (result == 0);
	cpu->cf = alu->carry;

	return result;
}
