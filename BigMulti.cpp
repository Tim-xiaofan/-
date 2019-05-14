#include <stdio.h>
#include <cstring>
#include <stdlib.h>

const int max_size = 257;
const int pre[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
const int e[10] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

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
	a[n] = '\0';//添加结束符
	for (int i = 0; i < m; i++) {
		b[i] = y[i + flag2];
	}
	b[m] = '\0';//添加结束符
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

int max(int a, int b) {
	int m = a;
	if (b > a)
		m = b;
	return m;
}

//划分a1, a0, b1, b0
void devide(char* a, char* b, char* a1, char* a0, char* b1, char* b0) {
	int a_len = strlen(a),b_len = strlen(b);
	int len = max(a_len, b_len);
	int half_n = 0;
	if (len % 2 == 0)  half_n = len / 2;
	else half_n = half_n = len / 2 + 1;
	//printf("half_n == %d\n", half_n);
	//a划分
	int m = a_len - half_n;
	if (m <= 0) { 
		a1[0] = '0';
		a1[1] = '\0';
		strcpy(a0, a);
	}
	else {
		for (int i = 0; i < m; i++)
			a1[i] = a[i];
		a1[m] = '\0';
		int j = 0, start = m;
		while (a[start] == '0') start++;//避免前置零
		for (int i = start; i < a_len; i++) {
			a0[j] = a[i];
			j++;
		}
		if (j == 0) { a0[0] = '0'; a0[1] = '\0'; }
		else a0[j] = '\0';
	}
	//b划分
	m = b_len - half_n;
	if (m <= 0) {//长度不足以拆分
		b1[0] = '0';
		b1[1] = '\0';
		strcpy(b0, b);
	}
	else {
		for (int i = 0; i < m; i++)
			b1[i] =b[i];
		b1[m] = '\0';
		int j = 0, start = m;
		while (b[start] == '0') start++;//避免前置零
		for (int i = start; i < b_len; i++) {
			b0[j] = b[i];
			j++;
		}
		if (j == 0) { b0[0] = '0'; b0[1] = '\0'; }
		else b0[j] = '\0';
	}
	//b划分
	//printf("a1 = %s, a0 = %s, b1 = %s, b0 = %s\n", a1, a0, b1, b0);
}

//字符窜转换为整数
void str_to_num(char* str, int* num) {
	int n = strlen(str);
	*num = 0;
	for (int i = 0; i < n; i++) {
		*num = (str[i] - '0') * e[n - 1 - i] + *num;
	}
}

//整数转字符窜
void num_to_str(int num, char* str) {
	char temp[9];
	int remain = num, count = 0;
	if (remain == 0) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	for (int i = 0; i < 9 && remain != 0; i++) {
		temp[i] = remain % 10;
		remain = remain / 10;
		count++;
	}
	for (int i = 0; i < count; i++)
		str[i] = temp[count - 1 - i] + '0';
	str[count] = '\0'; //结束符
}

//小整数数相乘(<=4,无符号)
void multi(char* a, char* b, char* c) {
	//printf("a = %s, b = %s\n", a, b);
	int s = 0, t = 0, result = 0;
	str_to_num(a, &s);
	str_to_num(b, &t);
	result = s * t;
	//printf("s = %d, t = %d, result == %d\n", s, t, result);
	num_to_str(result, c);
}

//小整数相加（<=8）
void add(char* a, char *b, char* c) {
	int a_len = strlen(a), b_len = strlen(b);
	int s = 0, t = 0, result = 0;
	//字符窜转换为整数
	str_to_num(a, &s);
	str_to_num(b, &t);
	result = s + t;
	//printf("s = %d, t = %d, result == %d\n", s, t, result);
	num_to_str(result, c);
}

//乘以10^n:末尾添加零
void add_tail(char* str, int n) {
	int j  = strlen(str);
	for (int i = 0; i < n; i++)
		str[j++] = '0';
	str[j] = '\0';
}

//大整数(无符号)相加(模拟手工计算)
void big_add(char* a, char* b, char* c) {
	int a_len = strlen(a), b_len = strlen(b), n = max(a_len, b_len);
	//printf("n = %d\n", n);
	int carry = 0;//进位
	char temp[max_size], ch;
	for (int i = 0; i < n; i++) {
		if (a_len > 0 && b_len > 0) {//做加法
			ch = a[--a_len] - '0' + b[--b_len] - '0' + carry;
			//printf("ch = %d\n", ch);
			if (ch >= 10) {
				carry = ch / 10;//进位
				temp[i] = (ch % 10) + '0';
			}
			else {
				carry = 0;
				temp[i] = ch + '0';
			}
		}
		else if (a_len <= 0 && b_len > 0) {
			ch = b[--b_len] - '0' + carry;
			//printf("ch = %d\n", ch);
			if (ch >= 10) {
				carry = ch / 10;//进位
				temp[i] = (ch % 10) + '0';
			}
			else {
				carry = 0;
				temp[i] = ch + '0';
			}
		}
		else if (a_len > 0 && b_len <= 0) {
			ch = a[--a_len] - '0' + carry;
			//printf("ch = %c\n", ch);
			if (ch >= 10) {
				carry = ch / 10;//进位
				temp[i] = (ch % 10) + '0';
			}
			else {
				carry = 0;
				temp[i] = ch + '0';
			}
		}
	}
	if (carry != 0) temp[n++] = '1';
	//printf("n = %d\n", n);
	for (int i = 0; i < n; i++)
		c[i] = temp[n - i - 1];
	c[n] = '\0';
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
/*
A = a1 * 10^(n/2) + a0
B = b1 * 10^(n/2) + b0
A * B = c2 * 10^n + c1 * 10^(n/2) + c0
其中：
c2 = a1 * b1
c1 = a0 * b1 + b0 * a1 = (a1 + a0) * (b1 + b0) - (c2 + c0)
*/

//大数相乘(无符号)
void big_multi(char* a, char* b, char* c) {
	//big_add(a, b, z);
	int a_len = strlen(a), b_len = strlen(b);
	int len = max(a_len, b_len);
	int half_n = 0;
	if (len % 2 == 0)  half_n = len / 2;
	else half_n = half_n = len / 2 + 1;
	if (len <= 4) {//递归结束
		multi(a, b, c);//小整数相乘
		//printf("c = %s\n", c);
		return;
	}
	//划分
	char a1[max_size], a0[max_size], b1[max_size], b0[max_size], c1[max_size], c0[max_size], c2[max_size];
	devide(a, b, a1, a0, b1, b0);
	printf("a1 = %s, a0 = %s, b1 = %s, b0 = %s\n", a1, a0, b1, b0);
	//计算c2, c1, c0
	//c2
	big_multi(a1, b1, c2);
	printf("c2 = a1 * b1 = %s\n", c2);
	//c0
	big_multi(a0, b0, c0);
	printf("c0 = a0 * b0 = %s\n", c0);
	//a0 * b1
	char temp1[max_size];
	big_multi(a0, b1, temp1);
	//printf("temp1 = a0 * b1 + b0 * a1 = %s\n", temp1);
	//b0 * a1
	char temp2[max_size];
	big_multi(b0, a1, temp2);
	//c1
	big_add(temp1, temp2, c1);
	printf("c1 = a0 * b1 + b0 * a1 = %s\n", c0);
	// c = c2 * 10^n + c1 * 10^(n/2) + c0
	//c2 = c2 * 10^n
	add_tail(c2, 2 * half_n);
	//c1 = c1 * 10^(n/2)
	add_tail(c1, half_n);
	//结果
	big_add(c2, c1, c);
	big_add(c0, c, c);
}

int main(int argc, char* argv[]) {
	char x[max_size];
	char y[max_size];
	scanf("%s%s", x, y);
	//printf("%s:%d, %s:%d\n", x, strlen(x), y, strlen(y));
	//if (suff(x[0], y[0]) == 0)printf("正数\n");
	//else printf("负数\n");
	char a[max_size];
	char b[max_size];
	pre_proc(x, y, a, b);
	//printf("a = %s, b = %s\n", a, b);
	char c[max_size * 2];
	big_multi(a, b, c);
	//big_add(a, b, c);
	printf("c = %s\n", c);
}



