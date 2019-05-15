/*主程序，进行计算器的功能选择*/
#include <stdio.h>
#include <cstring>
#include <stdlib.h>

extern "C" double add2(double a, double b);
extern "C" double sub2(double a, double b);
extern "C" double mul2(double a, double b);
extern "C" double div2(double a, double b);
extern "C" double angle_sin(double a);
extern "C" double angle_cos(double a);
extern "C" double angle_tan(double a);
extern "C" double result;
double result = 0;

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
	if (b == 0.0) {
		printf("除数不能为0\n");
		return;
	}
	div2(a, b);
	printf("商：%lf\n", result);
}

void msg() {
	printf("无效选项\n");
}

void angle_sin() {
	double angle = 0;
	printf("输入角度：");
	scanf("%lf", &angle);
	angle_sin(angle);
	printf("sin(%lf) = %lf \n", angle, result);
}

void angle_cos() {
	double angle = 0;
	printf("输入角度：");
	scanf("%lf", &angle);
	angle_cos(angle);
	printf("cos(%lf) = %lf \n", angle, result);
}

void angle_tan() {
	double angle = 0, f = 0, error = 1;
	printf("输入角度：");
	scanf("%lf", &angle);
	//角度不能为90的奇数倍
	int i = (int)angle;
	f = angle - i;
	if (f != 0.0) error = 0;
	else {
		int n = i / 90;
		if ((n % 2) == 0)error = 0;
	}
	if (error == 1) { printf("无效角度\n"); return; }
	angle_tan(angle);
	printf("tan(%lf) = %lf \n", angle, result);
}

void select() {
	int state = 0;
	printf("1.求和运算\n2.减法运算\n3.乘法运算\n4.除法运算\n\
5.sin函数\n6.cos函数\n7.tan函数\n8.大整数乘法\n0.退出程序\n");
	while (1) {
		printf("请选择功能：");
		scanf("%d", &state);
		switch (state){
		case 0: return;
		case 1: add(); break;
		case 2: sub(); break;
		case 3: mul(); break;
		case 4: div(); break;
		case 5: angle_sin(); break;
		case 6: angle_cos(); break;
		case 7: angle_tan(); break;
		default: msg(); break;
		}
	}
}

int main(int argv, char* argc[]) {
	void select();
	select();
}