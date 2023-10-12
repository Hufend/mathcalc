# 构建 mathcalc

在构建 mathcalc 之前  
我们要做一些准备

1. 获取 mathcalc 的源码
	- 见 [source.md](source.md)
2. 挑选合适的构建方法
	- [使用 CMake 构建 mathcalc](#使用-CMake-构建-mathcalc)
	- [使用 Make 构建 mathcalc](#使用-Make-构建-mathcalc)

另外构建时建议使用 `build` 作为构建目录 `<build>`

使用 CMake 构建 mathcalc
---------

本方法依赖

1. CMake (版本不小于3.10)
2. 任意的 C 编译器

在根目录 `<root>` 运行 `cmake`

	cd <root> && cmake . -B <build>

接下来切换到构建目录 `<build>` 运行 `cmake --build` 完成构建

	cd <build> && cmake --build

使用 Make 构建 mathcalc
--------

本方法依赖

1. Make
2. 任意的 C 编译器

在根目录 `<root>` 运行 `make`

	cd <root> && make

大功告成
