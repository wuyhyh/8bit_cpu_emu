# 项目根目录 Makefile，用于构建 CPU 模拟器

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99 -g

# 添加此行来控制是否开启调试打印
# make ENABLE_DUMP=1（定义宏），否则不定义
ifdef ENABLE_DUMP
CFLAGS += -DENABLE_DUMP
endif

ifdef ENABLE_DUMP
CFLAGS += -DENABLE_DUMP
endif

SRC_DIR = src
OBJ_DIR = build

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = cpuemu

.PHONY: all clean

all: $(TARGET)

# 链接最终可执行文件
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

# 编译每个 .c 文件为 .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
