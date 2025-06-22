#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>

/**
 * @file types.h
 * @brief 固定宽度整数类型定义，仿照 Linux 内核风格。
 */

/* 无符号整数类型 */
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

/* 有符号整数类型 */
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;

#endif /* _TYPES_H */
