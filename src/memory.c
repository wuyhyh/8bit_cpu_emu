#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "util.h"

void memory_init(struct memory *mem)
{
	memset(mem->data, 0, MEM_SIZE);
}

void memory_load(struct memory *mem, const u8 *src, u8 size)
{
	if (size > MEM_SIZE)
		panic("Program too large for memory");

	memcpy(mem->data, src, size);
}

u8 memory_read(struct memory *mem, u8 addr)
{
	if (addr >= MEM_SIZE)
		panic("Memory read out of bounds");

	return mem->data[addr];
}

void memory_write(struct memory *mem, u8 addr, u8 val)
{
	if (addr >= MEM_SIZE)
		panic("Memory write out of bounds");

	mem->data[addr] = val;
}
