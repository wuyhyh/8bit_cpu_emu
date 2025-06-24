#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "types.h"

/**
 * @file instructions.h
 * @brief 定义指令集中的 opcode 值（操作码）。
 */

/* 系统类指令 */
#define INSTR_NOP	0x00  /**< 空操作 */
#define INSTR_HALT	0xFF  /**< 停止模拟器 */
#define INSTR_LOAD_IMM  0x10  /**< LOAD Rn, imm */
#define INSTR_MOV       0x11  /**< MOV Rn, Rm */
#define INSTR_ADD       0x20  /**< ADD Rn, Rm */
#define INSTR_LOADM     0x12  /**< LOADM Rn, addr */
#define INSTR_STORE     0x13  /**< STORE Rn, addr */
#define INSTR_SUB       0x21  /**< SUB Rn, Rm */
#define INSTR_INC       0x22  /**< INC Rn */
#define INSTR_DEC       0x23  /**< DEC Rn */
#define INSTR_JMP	0x30  /**< 无条件跳转 */
#define INSTR_JZ	0x31  /**< 若 ZF==1 跳转 */
#define INSTR_JNZ	0x32  /**< 若 ZF==0 跳转 */
#define INSTR_JC	0x33  /**< 若 CF==1 跳转 */
#define INSTR_JNC	0x34  /**< 若 CF==0 跳转 */

#endif /* _INSTRUCTIONS_H */
