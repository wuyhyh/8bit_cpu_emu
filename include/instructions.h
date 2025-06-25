#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "types.h"

struct cpu;

/**
 * @file instructions.h
 * @brief 指令函数定义及分发表结构
 */

/**
 * 指令处理函数类型
 */
typedef void (*instr_fn_t)(struct cpu *cpu);

/**
 * 指令函数分发表：索引即为 opcode
 */
extern instr_fn_t instruction_table[256];

/**
 * instructions_init - 初始化指令函数表
 */
void instructions_init(void);

#endif /* _INSTRUCTIONS_H */
