#include <stdio.h>
#include "types.h"
#include "cpu.h"
#include "instructions.h"
#include "memory.h"
#include "util.h"

#define PROGRAM_MAX 256

int main(void)
{
	struct cpu cpu;
	struct memory mem;
	u8 prog_buf[PROGRAM_MAX];

	int size = load_hex_file("test/prog1.hex.txt", prog_buf, sizeof(prog_buf));
	if (size < 0) {
		fprintf(stderr, "Failed to load program.\n");
		return 1;
	}

	memory_init(&mem);
	memory_load(&mem, prog_buf, (u8)size);

#ifdef ENABLE_DUMP
	printf("Loaded memory contents:\n");
	dump_mem(mem.data, 32);  // 打印前 32 字节内容查看程序是否加载成功
#endif

	cpu_init(&cpu, &mem);

	instructions_init(); // 初始化函数表

	cpu_run(&cpu);

	return 0;
}
