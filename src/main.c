#include <stdio.h>
#include "types.h"
#include "cpu.h"
#include "memory.h"
#include "util.h"

#define PROGRAM_MAX 256

int main(void)
{
	struct cpu cpu;
	struct memory mem;
	u8 prog_buf[PROGRAM_MAX];

	int size = load_hex_file("test/prog1.hex", prog_buf, PROGRAM_MAX);
	if (size < 0) {
		fprintf(stderr, "Failed to load test/prog1.hex\n");
		return 1;
	}

	memory_init(&mem);
	memory_load(&mem, prog_buf, (u8)size);

	printf("Loaded memory contents:\n");
	dump_mem(mem.data, 32);  // 打印前 32 字节内容查看程序是否加载成功

	cpu_init(&cpu, &mem);

	cpu_run(&cpu);

	return 0;
}
