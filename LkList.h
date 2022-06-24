#ifndef __LK_LIST_H__
#define __LK_LIST_H__

#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define OK 1
#define ERROR 0

typedef int Status;

typedef struct DuLNode
{
	void* data;
	size_t n;
	struct DuLNode* prior;
	struct DuLNode* next;
}DuLNode, * DuLkList;


//��������ʼ��һ������ʵ���Ͼ��Ǵ���һ��ͷ���
Status InitList_DuL(DuLkList& L);

//���������һ������
Status ClearList_DuL(DuLkList& L);

//����������һ������
Status DestroyList_DuL(DuLkList& L);

//����������pָʾ���Ա�L�е�i���ڵ㲢����OK,iֵ���Ϸ�ʱ����ERROR
Status LocatePos_DuL(DuLkList L, int i, DuLNode*& p);

//��������Ԫ��e�����б���ǰ��
Status InsFirst_DuL(DuLkList& L, const void* e, size_t n);

//��������Ԫ��e�����б������
Status Append_DuL(DuLkList& L, const void* e, size_t n);

//�������ڵ�iλǰ����һ��Ԫ��e��nΪԪ��e�Ŀռ��С
Status ListInsert_DuL(DuLkList& L, int i, const void* e, size_t n);

//���������б���ǰ���Ԫ��ɾ��������Ԫ��e
Status DelFirst_DuL(DuLkList& L, void* e);

//���������б�������Ԫ��ɾ��������Ԫ��e
Status Remove_DuL(DuLkList& L, void* e);

Status ListDelete_DuL(DuLkList& L, int i, void* e);

//���������� ���Ը��Ӷ�������
Status ListTraverse_DuL(DuLkList L, Status(*visit)(const void*, void*), void* addition);

#endif // !__LK_LIST_H__
