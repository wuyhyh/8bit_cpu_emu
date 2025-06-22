#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "util.h"
#include "types.h"

/**
 * panic - 模拟器遇到致命错误，打印信息后退出
 * @msg: 错误描述字符串
 */
void panic(const char *msg)
{
	fprintf(stderr, "PANIC: %s\n", msg);
	exit(EXIT_FAILURE);
}

/**
 * dump_mem - 十六进制打印内存（调试用）
 * @data: 要打印的起始地址
 * @size: 字节数
 */
void dump_mem(const void *data, size_t size)
{
	const u8 *p = (const u8 *)data;
	size_t i;

	for (i = 0; i < size; i++) {
		if (i % 16 == 0)
			printf("%04zx: ", i);
		printf("%02x ", p[i]);
		if (i % 16 == 15)
			printf("\n");
	}
	if (i % 16 != 0)
		printf("\n");
}

int load_hex_file(const char *filename, u8 *buf, size_t max_len)
{
	FILE *fp = fopen(filename, "r");
	if (!fp) {
		perror("fopen");
		return -1;
	}

	size_t count = 0;
	while (count < max_len) {
		unsigned int byte;
		int ret = fscanf(fp, "%x", &byte);
		if (ret == EOF)
			break;
		if (ret != 1 || byte > 0xFF) {
			fprintf(stderr, "Invalid hex byte in file\n");
			fclose(fp);
			return -1;
		}
		buf[count++] = (u8)byte;
	}

	fclose(fp);
	return (int)count;
}
