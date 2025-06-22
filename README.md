# 8bit_cpu_emu

emulate a 8bit CPU

```
8bit_cpu_emu/
├── include/
│   ├── types.h           # 类型定义：u8、s8 等（仿 Linux）
│   ├── cpu.h             # struct cpu 定义、接口声明
│   ├── alu.h             # struct alu 定义、ALU操作接口
│   ├── memory.h          # 内存结构体与读写函数
│   ├── instructions.h    # 指令集常量与执行接口
│   └── util.h            # container_of 宏、调试工具
│
├── src/
│   ├── main.c            # 程序入口，初始化并运行模拟器
│   ├── cpu.c             # CPU 操作相关函数
│   ├── alu.c             # ALU 运算函数
│   ├── memory.c          # 内存相关操作
│   ├── instructions.c    # 指令执行逻辑实现
│   └── util.c            # 通用辅助函数实现（如打印、dump等）
│
├── test/
│   └── prog1.hex         # 示例机器码（手动写入或脚本生成）
│
├── Makefile              # 编译整个项目
└── README.md             # 项目说明文档（含 ISA 说明）
```