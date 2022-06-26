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

//��������ʼ��һ����ʽջ��ʵ���Ͼ��Ǵ���һ��ͷ���
Status InitStack_Lk(LkStack& S);

//�������ж�һ����ʽջS�Ƿ��ǿ�ջ
Status StackEmpty_Lk(LkStack S);

//��������һ����ʽջS�ĳ���
int StackLength_Lk(LkStack S);

//�����ʽջS
Status ClearStack_Lk(LkStack& S);

//������ʽջS
Status DestroyStack_Lk(LkStack& S);

//��ȡջ��Ԫ��
Status GetTop_Lk(LkStack S, void* e);

//��������ջ
Status Push_Lk(LkStack& S, const void* e, size_t n);

//��������ջ
Status Pop_Lk(LkStack& S, void* e);

#endif