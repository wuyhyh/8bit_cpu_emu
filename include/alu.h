#ifndef _ALU_H
#define _ALU_H

#include "types.h"

/**
 * @file alu.h
 * @brief 算术逻辑单元（ALU）结构与操作函数定义
 */

struct cpu; /* 前向声明 */

struct alu {
	u8 last_result; /**< 上次运算结果 */
	u8 carry;       /**< 进位标志 */
};

/**
 * alu_add - 执行加法，并更新 CPU 标志
 * @alu: 指向 ALU 实例
 * @a: 加数A
 * @b: 加数B
 * @return: 计算结果 (a + b)
 */
u8 alu_add(struct alu *alu, struct cpu *cpu, u8 a, u8 b);

/**
 * alu_sub - 执行减法，并更新 CPU 标志
 * @alu: 指向 ALU 实例
 * @a: 被减数
 * @b: 减数
 * @return: 计算结果 (a - b)
 */
u8 alu_sub(struct alu *alu, struct cpu *cpu, u8 a, u8 b);

/**
 * cpu_dump_state - 打印 CPU 当前状态（调试用）
 * @cpu: 指向 CPU 实例
 */
void cpu_dump_state(struct cpu *cpu);

#endif /* _ALU_H */
