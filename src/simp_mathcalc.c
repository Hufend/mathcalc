/*
 * 这是一个简单的计算器实现
 * 通常不做修改
 *
 * $ ./mathcalc
 * Type a mathematical equation
 * 1/7=
 * 0.142857
 */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define COLORLESS "\033[0m"
#define COLOR_ERROR "\033[1m\033[31m"
// 文件输入流
FILE *fd = NULL;
// 计算流程
double calculation();
// 加法
void internal_add(double *result, double *num, double *buf, uint8_t *mode) {
	mode[1] = 1;
	mode[2] = 1;
	*result += *num;
	*buf = *num;
}
// 减法
void internal_subtract(double *result, double *num, double *buf, uint8_t *mode) {
	mode[1] = 1;
	mode[2] = 0;
	*result -= *num;
	*buf = *num;
}
// 乘法
void internal_multiply(double *result, double *num, double *buf, uint8_t *mode) {
	if (mode[1] != 0) {
		if (mode[2] != 0)
			*result -= *buf;
		else
			*result += *buf;
		*buf *= *num;
		if (mode[2] != 0)
			*result += *buf;
		else
			*result -= *buf;
	} else
		*result *= *num;
}
// 除法
int internal_divide(double *result, double *num, double *buf, uint8_t *mode) {
	if (*num == 0)
		return EXIT_FAILURE;
	if (mode[1] != 0) {
		if (mode[2] != 0)
			*result -= *buf;
		else
			*result += *buf;
		*buf /= *num;
		if (mode[2] != 0)
			*result += *buf;
		else
			*result -= *buf;
	} else
		*result /= *num;
	return EXIT_SUCCESS;
}
double calculation() {
	uint8_t mode[3] = {0 /*运算模式*/, 0 /*是否经过加减运算*/, 0 /*加减运算区分*/};
	double result = 0;
	double num;
	double buf_plus_minus;
	int char_buf;
	// IO 交互
	if (!fscanf(fd, "%lf", &result))
		switch (fgetc(fd)) {
			case 'q':
			case 'e':
				exit(EXIT_SUCCESS);
			default:
				goto exception;
		}
loop:
	char_buf = fgetc(fd);
	switch (char_buf) {
		case '+':
			mode[0] = 1;
			if (!fscanf(fd, "%lf", &num))
				goto exception;
			internal_add(&result, &num, &buf_plus_minus, mode);
			break;
		case '-':
			mode[0] = 2;
			if (!fscanf(fd, "%lf", &num))
				goto exception;
			internal_subtract(&result, &num, &buf_plus_minus, mode);
			break;
		case '*':
			mode[0] = 3;
			if (!fscanf(fd, "%lf", &num))
				goto exception;
			internal_multiply(&result, &num, &buf_plus_minus, mode);
			break;
		case '/':
			mode[0] = 4;
			if (!fscanf(fd, "%lf", &num))
				goto exception;
			if (internal_divide(&result, &num, &buf_plus_minus, mode) == EXIT_FAILURE) {
				printf(COLOR_ERROR "Math error: the denominator cannot be 0" COLORLESS "\n");
				if (scanf("%*[^\n]%*c") == EOF)
					exit(EXIT_FAILURE);
				return NAN;
			}
			break;
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			goto loop;
		case '=':
		case ')':
		case ']':
		case '}':
			return result;
		default:
			printf(COLOR_ERROR "Unknown operator: %c" COLORLESS "\n", char_buf);
	}
	goto loop;
exception:
	switch (fgetc(fd)) {
		case '(':
		case '[':
		case '{':
			num = calculation();
			switch (mode[0]) {
				case 1:
					internal_add(&result, &num, &buf_plus_minus, mode);
					break;
				case 2:
					internal_subtract(&result, &num, &buf_plus_minus, mode);
					break;
				case 3:
					internal_multiply(&result, &num, &buf_plus_minus, mode);
					break;
				case 4:
					if (internal_divide(&result, &num, &buf_plus_minus, mode) == EXIT_FAILURE) {
						printf(COLOR_ERROR "Math error: the denominator cannot be 0" COLORLESS
						                   "\n");
						if (scanf("%*[^\n]%*c") == EOF)
							exit(EXIT_FAILURE);
						return NAN;
					}
					break;
				default:
					fprintf(stderr, COLOR_ERROR
					        "Fatal error: memory exception, no longer secure" COLORLESS "\n");
					exit(EXIT_FAILURE);
			}
			goto loop;
		default:
			printf(COLOR_ERROR "Math error: not a number" COLORLESS "\n");
			if (scanf("%*[^\n]%*c") == EOF)
				exit(EXIT_FAILURE);
	}
	return NAN;
}
int main(int argc, char **argv) {
	fd = stdin;
	if (argc > 1) {
		FILE *buf = fopen(argv[1], "r");
		if (buf == NULL)
			perror("File status");
		fd = buf;
	}
	printf("Type a mathematical equation\n");
	for (;;)
		printf("%f\n\n", calculation());
}
