#include "LkStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status InitStack_Lk(LkStack& S)
{
	int* length;
	S = (LkStack)malloc(sizeof(LNode));
	if (!S) exit(OVERFLOW);
	length = (int*)malloc(sizeof(int));//S->data为长度
	if (!length)exit(OVERFLOW);
	*length = 0;
	S->data = length;
	S->n = sizeof(int);
	S->next = NULL;
	return OK;
}

Status StackEmpty_Lk(LkStack S)
{
	return S->next == NULL;
}

int StackLength_Lk(LkStack S)
{
	int* length;
	length = (int*)S->data;
	return *length;
}

Status ClearStack_Lk(LkStack& S)
{
	int* length = (int*)S->data;
	LkStack p = S->next;
	while (p != NULL)			//就是不停地删除第一个元素，直到栈为空
	{
		S->next = p->next;
		free(p->data);
		free(p);
		p = S->next;
	}
	*length = 0;
	return OK;
}

Status DestroyStack_Lk(LkStack& S)
{
	ClearStack_Lk(S);			//先清空
	free(S->data);
	free(S);
	S = NULL;
	return OK;
}

Status GetTop_Lk(LkStack S, void* e)
{
	LkStack p;
	if (S->next == NULL)			//空栈
		return FALSE;
	p = S->next;
	memcpy(e, p->data, p->n);
	return TRUE;
}

Status Push_Lk(LkStack& S, const void* e, size_t n)
{
	int* length = (int*)S->data;
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
	(*length)++;
	return OK;
}

Status Pop_Lk(LkStack& S, void* e)
{
	int* length = (int*)S->data;
	LkStack p;
	if (S->next == NULL)			//空栈
		return FALSE;
	p = S->next;
	memcpy(e, p->data, p->n);
	S->next = p->next;
	free(p->data);
	free(p);
	(*length)--;
	return TRUE;
}