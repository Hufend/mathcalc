# 配置选项
cmake_minimum_required(VERSION 3.10)
project(mathcalc VERSION 1.0.1 LANGUAGE C)
# mathcalc 源文件
set(SRC_LIST src/simp_mathcalc.c)
# 编译选项
add_compile_options(-O1)
add_executable(${PROJECT_NAME} ${SRC_LIST})
