#ifndef _UTIL_H
#define _UTIL_H

#include <stddef.h>

/**
 * @file util.h
 * @brief 常用工具宏与调试函数声明
 */

 /**
  * container_of - 通过结构体成员指针获得整个结构体指针
  * @ptr: 成员的指针
  * @type: 容器结构体的类型
  * @member: 成员在结构体中的名称
  */
#define container_of(ptr, type, member) \
((type *)((char *)(ptr) - offsetof(type, member)))

/**
 * dump_mem - 打印内存的十六进制内容（调试用）
 * @data: 内存起始地址
 * @size: 打印字节数
 */
void dump_mem(const void *data, size_t size);

/**
 * panic - 模拟器内部错误，打印信息并退出
 * @msg: 错误描述
 */
void panic(const char *msg);

#endif /* _UTIL_H */
