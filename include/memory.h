#ifndef _MEMORY_H
#define _MEMORY_H

#include "types.h"

/**
 * @file memory.h
 * @brief 模拟 8 位内存结构和基本访问操作。
 */

#define MEM_SIZE 256  /**< 总内存大小：256 字节 */

/**
 * struct memory - 模拟的内存结构体
 */
struct memory {
	u8 data[MEM_SIZE];  /**< 内存数据存储数组 */
};

/**
 * memory_init - 初始化内存（清零）
 * @mem: 指向内存结构体
 */
void memory_init(struct memory *mem);

/**
 * memory_load - 将程序加载到内存前部
 * @mem: 内存指针
 * @src: 程序字节数组
 * @size: 要复制的字节数
 */
void memory_load(struct memory *mem, const u8 *src, u8 size);

/**
 * memory_read - 从内存中读取一个字节
 * @mem: 内存指针
 * @addr: 地址（0-255）
 * @return: 读取的字节值
 */
u8 memory_read(struct memory *mem, u8 addr);

/**
 * memory_write - 向内存中写入一个字节
 * @mem: 内存指针
 * @addr: 地址（0-255）
 * @val: 要写入的值
 */
void memory_write(struct memory *mem, u8 addr, u8 val);

#endif /* _MEMORY_H */
