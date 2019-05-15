/*主程序，进行计算器的功能选择*/
#include <stdio.h>
#include <cstring>
#include <stdlib.h>

extern "C" double add2(double a, double b);
extern "C" double sub2(double a, double b);
extern "C" double mul2(double a, double b);
extern "C" double div2(double a, double b);
extern "C" double result;
double result = 0;

int main(int argv, char* argc[]) {
	void select();
	select();
}

void add() {
	double a = 0, b = 0;
	printf("输入被加数：");
	scanf("%lf", &a);
	printf("输入加数：");
	scanf("%lf", &b);
	add2(a, b);
	printf("和：%lf\n",result);
}

void sub() {
	double a = 0, b = 0;
	printf("输入被减数：");
	scanf("%lf", &a);
	printf("输入减数：");
	scanf("%lf", &b);
	sub2(a, b);
	printf("差：%lf\n", result);
}

void mul() {
	double a = 0, b = 0;
	printf("输入被乘数：");
	scanf("%lf", &a);
	printf("输入乘数：");
	scanf("%lf", &b);
	mul2(a, b);
	printf("积：%lf\n", result);
}

void div() {
	double a = 0, b = 0;
	printf("输入被除数：");
	scanf("%lf", &a);
	printf("输入除数：");
	scanf("%lf", &b);
	div2(a, b);
	printf("商：%lf\n", result);
}

void select() {
	int state = 0;
	printf("1.求和运算\n2.减法运算\n3.乘法运算\n4.除法运算\n\
5.三角函数\n6.大整数乘法输入\n0.退出程序\n请选择功能：");
	while (1) {
		scanf("%d", &state);
		switch (state){
		case 0: return;
		case 1: add(); break;
		case 2: sub(); break;
		case 3: mul(); break;
		case 4: div(); break;
		default: break;
		}
	}
}