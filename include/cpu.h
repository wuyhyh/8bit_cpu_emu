#ifndef _CPU_H
#define _CPU_H

#include "types.h"
#include "alu.h"
#include "memory.h"

/**
 * @file cpu.h
 * @brief 定义 8 位 CPU 的结构体和接口。
 */

struct cpu {
	u8 regs[4];          /**< 通用寄存器 R0-R3 */
	u8 pc;               /**< 程序计数器 */
	u8 zf;               /**< 零标志 */
	u8 cf;               /**< 进位标志 */
	struct alu alu;      /**< 嵌入的算术逻辑单元 */
	struct memory *mem;  /**< 指向内存对象 */
};

/**
 * cpu_init - 初始化 CPU 状态
 * @cpu: 指向 CPU 结构体
 * @mem: 指向内存结构体
 */
void cpu_init(struct cpu *cpu, struct memory *mem);

/**
 * cpu_run - 执行模拟器主循环
 * @cpu: 指向已初始化的 CPU
 */
void cpu_run(struct cpu *cpu);

#endif /* _CPU_H */
