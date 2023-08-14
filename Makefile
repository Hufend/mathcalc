# 变量定义
BUILD_DIR ?= build
SRC_LIST := $(patsubst %, $(BUILD_DIR)/src/%.o, mathcalc)
CC ?= gcc

.SECONDARY: $(SRC_LIST)

.PHONY: clean configure

all: configure $(BUILD_DIR)/mathcalc
	$(info Done)

# 清理中间文件
clean:
	$(info Cleaning up project)
	@rm -r $(BUILD_DIR)/src

# 配置
configure:
	$(info Configuring)
	@mkdir -p $(BUILD_DIR) $(BUILD_DIR)/src

# 链接 mathcalc
$(BUILD_DIR)/mathcalc: $(SRC_LIST)
	$(info Linking $< to $@)
	@$(CC) -o $@ $<

# 编译源码
$(BUILD_DIR)/src/%.o: src/%.c
	$(info Compiling $< to $@)
	@$(CC) -c -O1 -o $@ $<
