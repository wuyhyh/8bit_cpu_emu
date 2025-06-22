#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "types.h"

/**
 * @file instructions.h
 * @brief 定义指令集中的 opcode 值（操作码）。
 */

/* 系统类指令 */
#define INSTR_NOP   0x00  /**< 空操作 */
#define INSTR_HALT  0xFF  /**< 停止模拟器 */

#endif /* _INSTRUCTIONS_H */
