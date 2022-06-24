#ifndef __LK_STACK_H__
#define __LK_STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Status InitStack_Lk(LkStack& S)
{
	S = (LkStack)malloc(sizeof(LNode));
	if (!S) exit(OVERFLOW);
	S->data = NULL;
	S->next = NULL;
	return OK;
}

//函数：判断一个链式栈S是否是空栈
Status StackEmpty_Lk(LkStack S)
{
	return S->next == NULL;
}

//函数：求一个链式栈S的长度
int StackLength_Lk(LkStack S)
{
	int n = 0;
	LkStack p = S;
	while (p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return n;
}

//清空链式栈S
Status ClearStack_Lk(LkStack& S)
{
	LkStack p = S->next;
	while (p != NULL)			//就是不停地删除第一个元素，直到栈为空
	{
		S->next = p->next;
		free(p->data);
		free(p);
		p = S->next;
	}
	return OK;
}

//销毁链式栈S
Status DestroyStack_Lk(LkStack& S)
{
	ClearStack_Lk(S);			//先清空
	free(S);
	S = NULL;
	return OK;
}

//获取栈顶元素
Status GetTop_Lk(LkStack S, void* e)
{
	LkStack p;
	if (S->next == NULL)			//空栈
		return FALSE;
	p = S->next;
	memcpy(e, p->data, p->n);
	return TRUE;
}

//函数：入栈
Status Push_Lk(LkStack& S, const void* e, size_t n)
{
	LkStack t;
	char* buffer;
	t = (LkStack)malloc(sizeof(LNode));
	if (!t)exit(OVERFLOW);
	buffer = (char*)malloc(n);
	if (!buffer)exit(OVERFLOW);
	memcpy(buffer, e, n);
	t->data = buffer;
	t->n = n;
	t->next = S->next;
	S->next = t;
	return OK;
}

//函数：出栈
Status Pop_Lk(LkStack& S, void* e)
{
	LkStack p;
	if (S->next == NULL)			//空栈
		return FALSE;
	p = S->next;
	memcpy(e, p->data, p->n);
	S->next = p->next;
	free(p->data);
	free(p);
	return TRUE;
}

#endif