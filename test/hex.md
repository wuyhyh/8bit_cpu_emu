# 机器指令

- idle halt

```text
00 00 ff
```

- load mov add

```text
10 00 05
10 01 07
20 00 01
11 02 00
ff
```

- 内存加载到寄存器 寄存器存放回内存

```text
10 00 2A      ; LOAD R0, 0x2A (42)
13 00 F0      ; STORE R0, 0xF0
12 01 F0      ; LOADM R1, 0xF0
FF            ; HALT
```

```text
10 00 2A 13 00 F0 12 01 F0 FF
```

- 算术指令

```text
10 00 0A      ; LOAD R0, 10
10 01 03      ; LOAD R1, 3
21 00 01      ; SUB R0, R1 => 7
22 01         ; INC R1 => 4
11 02 00      ; MOV R2, R0
23 02         ; DEC R2 => 6
11 03 01      ; MOV R3, R1
22 03         ; INC R3 => 5
FF            ; HALT
```

```text
10 00 0A 10 01 03 21 00 01 22 01 11 02 00 23 02 11 03 01 22 03 FF
```

- 跳转指令
```text
LOAD R0, 0     ; R0 = 0
LOAD R1, 1     ; R1 = 1
SUB R0, R1     ; R0 = 0 - 1 => ZF = 0, CF = 1
JZ 0x0A        ; 不跳转
JMP 0x0D       ; 跳转，跳过 HALT
HALT           ; 不会执行
LOAD R2, 42    ; 被跳转执行
HALT
```
```text
10 00 00
10 01 01
21 00 01
31 0A
30 0D
FF
10 02 2A
FF
```