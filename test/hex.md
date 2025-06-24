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

- loadm store
```text
10 00 2A      ; LOAD R0, 0x2A (42)
13 00 F0      ; STORE R0, 0xF0
12 01 F0      ; LOADM R1, 0xF0
FF            ; HALT
```
```text
10 00 2A 13 00 F0 12 01 F0 FF
```