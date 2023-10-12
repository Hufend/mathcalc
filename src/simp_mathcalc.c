/*
 * 这是一个简单的计算器实现
 * 通常不做修改
 *
 * $ ./mathcalc
 * 1/7
 * 0.142857
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// 文件输入流
FILE *source = NULL;
// 计算流程
double calculation();
// 加法
void internal_add(double *result, double *number, double *buffer, uint8_t *mode) {
	mode[1] = 1;
	mode[2] = 1;
	*result += *number;
	*buffer = *number;
}
// 减法
void internal_subtract(double *result, double *number, double *buffer, uint8_t *mode) {
	mode[1] = 1;
	mode[2] = 0;
	*result -= *number;
	*buffer = *number;
}
// 乘法
void internal_multiply(double *result, double *number, double *buffer, uint8_t *mode) {
	if (mode[1] != 0) {
		if (mode[2] != 0)
			*result -= *buffer;
		else
			*result += *buffer;
		*buffer *= *number;
		if (mode[2] != 0)
			*result += *buffer;
		else
			*result -= *buffer;
	} else
		*result *= *number;
}
// 除法
int internal_divide(double *result, double *number, double *buffer, uint8_t *mode) {
	if (*number == 0)
		return EXIT_FAILURE;
	if (mode[1] != 0) {
		if (mode[2] != 0)
			*result -= *buffer;
		else
			*result += *buffer;
		*buffer /= *number;
		if (mode[2] != 0)
			*result += *buffer;
		else
			*result -= *buffer;
	} else
		*result /= *number;
	return EXIT_SUCCESS;
}
double calculation() {
	// 计算模式
	uint8_t mode[3] = {0 /*运算模式*/, 0 /*是否经过加减运算*/, 0 /*加减运算区分*/};
	// 计算结果
	double result = 0;
	double number;
	double buffer_plus_minus;
	int operator_buffer;
	// IO 交互
start:
	printf("\033[0m");
	if (!fscanf(source, "%lf", &result)) {
		switch (fgetc(source)) {
			case 'q':
			case 'e':
			case EOF:
				exit(EXIT_SUCCESS);
			case 'h':
				printf("Type a mathematical formula\n");
				break;
			default:
				goto exception;
		}
		goto start;
	}
loop:
	operator_buffer = fgetc(source);
	switch (operator_buffer) {
		case '+':
			mode[0] = 1;
			if (!fscanf(source, "%lf", &number))
				goto exception;
			internal_add(&result, &number, &buffer_plus_minus, mode);
			break;
		case '-':
			mode[0] = 2;
			if (!fscanf(source, "%lf", &number))
				goto exception;
			internal_subtract(&result, &number, &buffer_plus_minus, mode);
			break;
		case '*':
			mode[0] = 3;
			if (!fscanf(source, "%lf", &number))
				goto exception;
			internal_multiply(&result, &number, &buffer_plus_minus, mode);
			break;
		case '/':
			mode[0] = 4;
			if (!fscanf(source, "%lf", &number))
				goto exception;
			if (internal_divide(&result, &number, &buffer_plus_minus, mode) == EXIT_FAILURE) {
				fprintf(stderr, "\033[0m\033[1m\033[31mMath error: The denominator cannot be 0\n");
				scanf("%*[^\n]%*c");
				goto start;
			}
			break;
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			goto loop;
		case EOF:
			exit(EXIT_SUCCESS);
		case '=':
		case ')':
		case ']':
		case '}':
			return result;
		default:
			printf("\033[0m\033[1m\033[31mUnknown operator: %c\n", operator_buffer);
	}
	goto loop;
exception:
	switch (fgetc(source)) {
		case '(':
		case '[':
		case '{':
			number = calculation();
			switch (mode[0]) {
				case 1:
					internal_add(&result, &number, &buffer_plus_minus, mode);
					break;
				case 2:
					internal_subtract(&result, &number, &buffer_plus_minus, mode);
					break;
				case 3:
					internal_multiply(&result, &number, &buffer_plus_minus, mode);
					break;
				case 4:
					if (internal_divide(&result, &number, &buffer_plus_minus, mode) == EXIT_FAILURE) {
						fprintf(stderr,
						        "\033[0m\033[1m\033[31mMath error: the denominator cannot be 0\n");
						scanf("%*[^\n]%*c");
						goto start;
					}
					break;
				default:
					printf("\033[0m\033[1m\033[31mProgram error: Memory exception\n");
					exit(EXIT_FAILURE);
			}
			goto loop;
		default:
			fprintf(stderr, "\033[0m\033[1m\033[31mMath error: NaN\n");
			scanf("%*[^\n]%*c");
	}
	goto start;
}
int main(int argc, char **argv) {
	if (argc > 1) {
		source = fopen(argv[1], "r");
		if (source == NULL) {
			perror("Status");
			source = stdin;
		}
	} else
		source = stdin;
	for (;;)
		printf("%f\n\n", calculation());
}
