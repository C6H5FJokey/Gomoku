#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define OK 1

typedef int Status;

typedef struct LNode
{
	void* data;
	size_t n;
	struct LNode* next;
}LNode, * LkStack;

//函数：初始化一个链式栈，实际上就是创建一个头结点
Status InitStack_Lk(LkStack& S);

//函数：判断一个链式栈S是否是空栈
Status StackEmpty_Lk(LkStack S);

//函数：求一个链式栈S的长度
int StackLength_Lk(LkStack S);

//清空链式栈S
Status ClearStack_Lk(LkStack& S);

//销毁链式栈S
Status DestroyStack_Lk(LkStack& S);

//获取栈顶元素
Status GetTop_Lk(LkStack S, void* e);

//函数：入栈
Status Push_Lk(LkStack& S, const void* e, size_t n);

//函数：出栈
Status Pop_Lk(LkStack& S, void* e);

#endif