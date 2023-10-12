BUILD_DIR ?= build
MOD_LIST := $(patsubst %, $(BUILD_DIR)/src/%.o, simp_mathcalc)
CC ?= gcc
CFLAGS ?= -O1

.SECONDARY: $(MOD_LIST)

.PHONY: clean init

all: init $(BUILD_DIR)/simp_mathcalc
	$(info Done!)

# 清理中间文件
clean:
	$(info Cleaning up...)
	@rm -r $(BUILD_DIR)/src

# 初始化
init:
	$(info Initializing...)
	@mkdir -p $(BUILD_DIR) $(BUILD_DIR)/src

# 链接 simple mathcalc
$(BUILD_DIR)/simp_mathcalc: $(MOD_LIST)
	$(info Linking $< to $@)
	@$(CC) -o $@ $<

# 编译源码
$(BUILD_DIR)/src/%.o: src/%.c
	$(info Compiling $< to $@)
	@$(CC) -c $(CFLAGS) -o $@ $<
