# mathcalc

	                |    |                 |      
	   ` \    _` |   _|    \    _|   _` |  |   _| 
	 _|_|_| \__,_| \__| _| _| \__| \__,_| _| \__| 

[GNU General Public License Version 3](LICENSE.md)

[![License](https://img.shields.io/badge/License-GNU_GPL_v3-green)](../../LICENSE.md)
![Version](https://img.shields.io/badge/Version-_1.0.1-blue)

介绍
---------

### 概要

**mathcalc** 是一个支持四则运算的简易控制台计算器

其他没什么好介绍的了

这只是我的一个练手的小玩具=)

### 特性

~~mathcalc 没有任何特性!!~~

1. 支持四则运算
2. 支持括号优先级
3. 自动忽略空白字符

安装
---------

安装 mathcalc 通常有 2 个办法

1. [构建源码](docs/build.md)
2. [下载发行的软件包](docs/source.md)

用法
---------

mathcalc 非常易用~~, 毕竟它只支持四则运算~~

当你运行 mathcalc 的时候, 它会提示你输入一个算式

	$ ./simp_mathcalc
	Type a mathematical equation
	1/7=
	0.142857

此时你可以输入算式以计算 这里的 `1/7=` 是用户输入

mathcalc 在处理用户输入时会忽略空白字符 即 `\s` / `\t` / `\n` / `\r`

以下为实例

	5 /      7     =
	0.714286

	7  + 8745 / 3   - 73.145 
	- 6 * ( 5 +    8
	/ 2 )
	=
	2794.855000

	4*(7+4)+55-91=
	8.000000

支持
---------

本项目目前只有一名维护者  
如果有问题可以与我联系 ~~, 但并不是那么及时~~  

Email: <mailto:macrohard@yeah.com>  
QQ: 1245407374

当然也可以提 issue
