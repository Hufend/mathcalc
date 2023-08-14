# 构建 mathcalc

在构建 mathcalc 之前  
我们要做一些准备

1. 获取 mathcalc 的源码
	- 可查看 [source.md](source.md)
2. 挑选合适的构建方法
	- [使用 CMake 构建 mathcalc](#使用-CMake-构建-mathcalc), 通用的办法
	- [使用 Make 构建 mathcalc](#使用-Make-构建-mathcalc), 不一定可行的办法, 不推荐使用

接着来做几个小约定

- `<root>` - mathcalc 的根目录  
- `<build directory>` - mathcalc 的目标文件存放的目录  
- `<generator>` - CMake 的目标文件生成器

使用 CMake 构建 mathcalc
---------

本方法依赖如下

1. CMake (版本不小于3.10)
2. 任意的 C 编译器
3. 可以通过 CMake 生成的目标文件进行构建的任何软件
	- Make
	- Ninja
	- CodeBlocks
	- ...

在 mathcalc 的根目录下运行 `cmake`

	cd <root> && cmake -S <root> -B <build directory> -G <generator>

接下来切换到 `<build directory>`
运行 `cmake -build`

	cd <build directory> && cmake --build

使用 Make 构建 mathcalc
--------

本方法依赖如下

1. Make
2. 任意的 C 编译器

在 mathcalc 的根目录下运行 `make`

	cd <root> && make BUILD_DIR=<build directory>

此命令可以自定义参数

此方法简单但不推荐使用
