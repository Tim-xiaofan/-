.386	;框架伪指令				
							
.model flat;定义程序的工作模式	
							
option casemap:none		;告诉编译器程序大小写敏感，因为win32API大小写敏感
;include 文件定义
includelib msvcrt.lib   ;库文件
printf PROTO C:ptr sbyte, :VARARG ;函数声明
scanf PROTO C:ptr sbyte, :VARARG
public add2 ;允许被C模块使用
public sub2
public mul2
public div2
extern _result: real8 ;来自C模块

;数据段
.data					
	;定义这些分段是把不同类型的数据或代码归类，放到不同的属性内存页中，dos下定义是赋值给寄存器
;代码段
.code					;所有指令都必须放在代码段，在可执行文件中，代码段放在_TEXT节区（区块）中）

;加法
add2 proc C a:real8, b:real8 ;使用c规则
    finit ;初始化堆栈
    fld a
    fld b
    fadd st(0), st(1);
    fst _result
    ret
add2 endp

;减法
sub2  proc C a:real8, b:real8 ;使用c规则
    finit ;初始化堆栈
    fld b
    fld a
    fsub st(0), st(1);
    fst _result
    ret
sub2 endp

;乘法
mul2 proc C a:real8, b:real8 ;使用c规则
    finit ;初始化堆栈
    fld a
    fld b
    fmul st(0), st(1);
    fst _result
    ret
mul2 endp

;除法
div2 proc C a:real8, b:real8 ;使用c规则
    finit ;初始化堆栈
    fld b
    fld a
    fdiv st(0), st(1);
    fst _result
    ret
div2 endp
end ;必须使用
