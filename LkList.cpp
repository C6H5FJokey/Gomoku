#include "LkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status InitList_DuL(DuLkList& L)
{
	L = (DuLkList)malloc(sizeof(DuLNode));
	if (!L)exit(OVERFLOW);
	int* length = (int*)malloc(sizeof(int));//L->data为长度
	if (!length)exit(OVERFLOW);
	*length = 0;
	L->data = length;//L->data为length
	L->prior = L;
	L->next = L;
	return OK;
}

Status ClearList_DuL(DuLkList& L) {
	int* length = (int*)L->data;
	DuLNode* p = L->next;
	while (p != L)
	{
		L->next = p->next;
		free(p->data);
		free(p);
		p = L->next;
	}
	L->prior = L;
	*length = 0;
	return OK;
}

Status DestroyList_DuL(DuLkList& L) {
	ClearList_DuL(L);
	free(L->data);
	free(L);
	L = NULL;
	return OK;
}

Status LocatePos_DuL(DuLkList L, int i, DuLNode*& p) {
	const int* length = (int*)L->data;
	int j;
	if (i<1 || i>*length)return ERROR;
	p = L;
	if (i <= *length / 2) {//前半部分 使用正序
		for (j = 0; j < i; j++) p = p->next;
	}
	else//后半部分 使用倒序
	{
		for (j = *length; j >= i; j--) p = p->prior;
	}
	return OK;
}

Status InsFirst_DuL(DuLkList& L, const void* e, size_t n) {
	DuLNode* s;
	char* buffer;
	int* length = (int*)L->data;
	s = (DuLNode*)malloc(sizeof(DuLNode));
	if (!s)exit(OVERFLOW);
	buffer = (char*)malloc(n);
	if (!buffer)exit(OVERFLOW);
	memcpy(buffer, e, n);
	s->data = buffer;
	s->n = n;
	s->next = L->next;
	L->next = s;
	s->prior = L;
	s->next->prior = s;
	(*length)++;
	return OK;
}

Status Append_DuL(DuLkList& L, const void* e, size_t n) {
	DuLNode* s;
	char* buffer;
	int* length = (int*)L->data;
	s = (DuLNode*)malloc(sizeof(DuLNode));
	if (!s)exit(OVERFLOW);
	buffer = (char*)malloc(n);
	if (!buffer)exit(OVERFLOW);
	memcpy(buffer, e, n);
	s->data = buffer;
	s->n = n;
	s->prior = L->prior;
	L->prior = s;
	s->next = L;
	s->prior->next = s;
	(*length)++;
	return OK;
}

Status ListInsert_DuL(DuLkList& L, int i, const void* e, size_t n) {
	DuLNode* p;
	DuLNode* s;
	char* buffer;
	int* length = (int*)L->data;
	if (i<1 || i>*length + 1) return ERROR;
	if (i == 1) {
		return InsFirst_DuL(L, e, n);
	}
	else if (i == *length + 1)
	{
		return Append_DuL(L, e, n);
	}
	else
	{
		LocatePos_DuL(L, i, p);
		s = (DuLNode*)malloc(sizeof(DuLNode));
		if (!s)exit(OVERFLOW);
		buffer = (char*)malloc(n);
		if (!buffer)exit(OVERFLOW);
		memcpy(buffer, e, n);
		s->data = buffer;
		s->n = n;
		s->prior = p->prior;
		p->prior = s;
		s->next = p;
		s->prior->next = s;
		(*length)++;
		return OK;
	}
}

Status DelFirst_DuL(DuLkList& L, void* e) {
	DuLNode* q;
	int* length = (int*)L->data;
	q = L->next;
	q->prior->next = q->next;
	q->next->prior = q->prior;
	memcpy(e, q->data, q->n);
	free(q->data);
	free(q);
	(*length)--;
	return OK;
}

Status Remove_DuL(DuLkList& L, void* e) {
	DuLNode* q;
	int* length = (int*)L->data;
	q = L->prior;
	q->prior->next = q->next;
	q->next->prior = q->prior;
	memcpy(e, q->data, q->n);
	free(q->data);
	free(q);
	(*length)--;
	return OK;
}

Status ListDelete_DuL(DuLkList& L, int i, void* e) {
	DuLNode* q;
	int* length = (int*)L->data;
	if (i<1 || i>*length) return ERROR;
	if (i == 1) {
		return DelFirst_DuL(L, e);
	}
	else if (i == *length)
	{
		return Remove_DuL(L, e);
	}
	else
	{
		LocatePos_DuL(L, i, q);
		q->prior->next = q->next;
		q->next->prior = q->prior;
		memcpy(e, q->data, q->n);
		free(q->data);
		free(q);
		(*length)--;
		return OK;
	}
}

Status ListTraverse_DuL(DuLkList L, Status(*visit)(const void*, void*), void* addition) {
	DuLNode* p = L;
	while (p->next != L)
	{
		p = p->next;
		if (!visit(p->data, addition))return ERROR;
	}
	return OK;
}