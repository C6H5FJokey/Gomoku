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

//��������ʼ��һ����ʽջ��ʵ���Ͼ��Ǵ���һ��ͷ���
Status InitStack_Lk(LkStack& S)
{
	S = (LkStack)malloc(sizeof(LNode));
	if (!S) exit(OVERFLOW);
	S->data = NULL;
	S->next = NULL;
	return OK;
}

//�������ж�һ����ʽջS�Ƿ��ǿ�ջ
Status StackEmpty_Lk(LkStack S)
{
	return S->next == NULL;
}

//��������һ����ʽջS�ĳ���
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

//�����ʽջS
Status ClearStack_Lk(LkStack& S)
{
	LkStack p = S->next;
	while (p != NULL)			//���ǲ�ͣ��ɾ����һ��Ԫ�أ�ֱ��ջΪ��
	{
		S->next = p->next;
		free(p->data);
		free(p);
		p = S->next;
	}
	return OK;
}

//������ʽջS
Status DestroyStack_Lk(LkStack& S)
{
	ClearStack_Lk(S);			//�����
	free(S);
	S = NULL;
	return OK;
}

//��ȡջ��Ԫ��
Status GetTop_Lk(LkStack S, void* e)
{
	LkStack p;
	if (S->next == NULL)			//��ջ
		return FALSE;
	p = S->next;
	memcpy(e, p->data, p->n);
	return TRUE;
}

//��������ջ
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

//��������ջ
Status Pop_Lk(LkStack& S, void* e)
{
	LkStack p;
	if (S->next == NULL)			//��ջ
		return FALSE;
	p = S->next;
	memcpy(e, p->data, p->n);
	S->next = p->next;
	free(p->data);
	free(p);
	return TRUE;
}

#endif