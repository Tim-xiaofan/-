#include <stdio.h>
#include <cstring>
#include <stdlib.h>

const int max_size = 257;
const int pre[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
const int e[4] = { 1, 10, 100, 1000 };

//判断符号,-0输出为0
int suff(char x_suff, char y_suff) {
	if ((x_suff == '-' && y_suff == '-') || (x_suff != '-' && y_suff != '-'))return 0;//同好为正
	else return -1;
}

//预处理:除去符号
void pre_proc(char* x, char* y, char* a, char* b){
	int n = 0, m = 0, max = 0;
	//得到无符号长度
	n = strlen(x);
	m = strlen(y);
	int flag1 = 0, flag2 = 0;
	if (x[0] == '-') { n = n - 1; flag1 = 1; }
	if (y[0] == '-') { m = m - 1; flag2 = 1; }
	for (int i = 0; i < n; i++) {
		a[i] = x[i + flag1];
	}
	for (int i = 0; i < m; i++) {
		b[i] = y[i + flag2];
	}
	/*//取较大的长度
	max = n;
	if (n < m) max = m;
	printf("n = %d, m = %d, max = %d\n", n, m, max);
	//补充为2幂的长
	int len = 0;
	for (int i = 0; i < 10; i++) {
		if (max <= pre[i]) { 
			len = pre[i];
			break;
		}
	}
	printf("len = %d\n", len);
	//添加前置零
	int deta = len - n;
	for (int i = 0; i < len; i++) {
		if (i < deta) a[i] = '0';
		else a[i] = x[i - deta + flag1];
	}
	a[len] = '\0';//添加结束符
	deta = len - m;
	for (int i = 0; i < len; i++) {
		if (i < deta) b[i] = '0';
		else b[i] = y[i - deta + flag2];
	}
	b[len] = '\0';*/
}

//划分a1, a0, b1, b0
void devide(char* a, char* b, char* a1, char* a0, char* b1, char* b0) {
	int len = strlen(a);
	int n = len / 2;
	//a
	for (int i = 0; i < n; i++)
		a1[i] = a[i];
	a1[n] = '\0';
	int j = 0;
	for (int i = n; i < len; i++) {
		a0[j] = a[i];
		j++;
	}
	a0[j] = '\0';
	//b
	for (int i = 0; i < n; i++)
		b1[i] = b[i];
	b1[n] = '\0';
	j = 0;
	for (int i = n; i < len; i++) {
		b0[j] = b[i];
		j++;
	}
	b0[j] = '\0';
	//printf("a1 = %s, a0 = %s, b1 = %s, b0 = %s\n", a1, a0, b1, b0);
}

//小整数数相乘(<=2)
void multi(char* a, char* b, char* z) {
	//printf("a = %s, b = %s\n", a, b);
	int len = strlen(a);
	int s = 0, t = 0, result = 0;
	//字符窜转换为整数
	for (int i = 0; i < len; i++) {
		s = (a[i] - '0') * e[len - 1 - i] + s;
		t = (b[i] - '0') * e[len - 1 - i] + t;
	}
	result = s * t;
	//整数转字符窜
	char temp[4];
	int remain = result, count = 0;
	for (int i = 0; i < 5 && remain != 0; i++) {
		temp[i] = remain % 10;
		remain = remain / 10;
		count++;
	}
	for (int i = 0; i < count; i++)
		z[i] = temp[count - 1 - i] + '0';
	//printf("s = %d, t = %d, result == %d\n", s, t, result);
	z[count] = '\0'; //结束符
	printf("z = %s\n", z);
}

//小整数相加（<=4）
void add(char* a, char *b, char* c) {
	int len = strlen(a);
	int s = 0, t = 0, result = 0;
	//字符窜转换为整数
	for (int i = 0; i < len; i++) {
		s = (a[i] - '0') * e[len - 1 - i] + s;
		t = (b[i] - '0') * e[len - 1 - i] + t;
	}
	result = s + t;
	//整数转字符窜
	char temp[5];
	int remain = result, count = 0;
	for (int i = 0; i < 5 && remain != 0; i++) {
		temp[i] = remain % 10;
		remain = remain / 10;
		count++;
	}
	for (int i = 0; i < count; i++)
		c[i] = temp[count - 1 - i] + '0';
	//printf("s = %d, t = %d, result == %d\n", s, t, result);
	c[count] = '\0'; //结束符
	//printf("c = %s\n", c);
}

//乘以10^n:末尾添加零
void add_tail(char* a, int n) {
	int len = strlen(a);
	for (int i = 0; i < n; i++)
		a[i] = '0';
	a[len + n] = '\0';
}

//大整数(无符号)相加
void big_add(char* a, char* b, char* c) {
	int len = strlen(a);
	if (len <= 4) {
		add(a, b, c);//小整数相加
		return;
	}
	char a1[max_size], a0[max_size], b1[max_size], b0[max_size], d1[max_size], d0[max_size];
	devide(a, b, a1, a0, b1, b0);
	big_add(a1, b1, d1);
	big_add(a0, b0, d0);
	//乘以10^n:末尾添加零
	printf("d1 = %s\n", d1);
	add_tail(d1, len / 2);
	printf("d1 = %s\n", d1);
}

//计算c2, c1, c0
void get_c(char* a1, char * a0, char* b1, char* b0, char* c2, char* c1, char* c0) {
	void big_multi(char* x, char* y, char* z);
	big_multi(a1, b1, c2);//c2
	char temp1[max_size], temp2[max_size];
	big_multi(a0, b1, temp1);
	big_multi(a1, b0, temp2);
	big_add(temp1, temp2, c1);//c1
	big_multi(a0, b0, c0);//c0
}

//大数相乘
void big_multi(char* x, char* y, char* z) {
	char a[max_size]; //无符号数
	char b[max_size];
	pre_proc(x, y, a, b);//除去符号，添加前置零
	big_add(a, b, z);
	/*int len = strlen(a);
	if (len <= 2)//递归结束
		multi(a, b, z);//小整数相乘
	//划分
	char a1[max_size], a0[max_size], b1[max_size], b0[max_size], c1[max_size], c0[max_size], c2[max_size];
	devide(a, b, a1, a0, b1, b0);
	//printf("a1 = %s, a0 = %s, b1 = %s, b0 = %s\n", a1, a0, b1, b0);
	//计算c2, c1, c0*/
}

int main(int argc, char* argv[]) {
	char x[max_size];
	char y[max_size];
	scanf("%s%s", x, y);
	printf("%s:%d, %s:%d\n", x, strlen(x), y, strlen(y));
	if (suff(x[0], y[0]) == 0)printf("正数\n");
	else printf("负数\n");
	char a[max_size];
	char b[max_size];
	//pre_proc(x, y, a, b);
	//printf("a = %s, b = %s\n", a, b);
	char z[max_size * 2];
	big_multi(x, y, z);
}



