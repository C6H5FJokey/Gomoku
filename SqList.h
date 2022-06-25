#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define OK 1
#define ERROR 0

#define LIST_INIT_SIZE 8

typedef int Status;

typedef struct
{
	void* data;
	size_t n;
}SqNode;

typedef struct
{
	SqNode* elem;
	int length;
	int listsize;
}SqList;


//��������ʼ��һ������ʵ���Ͼ��Ǵ���һ��ͷ���
Status InitList_Sq(SqList& L);

//���������һ������
Status ClearList_Sq(SqList& L);

//����������һ������
Status DestroyList_Sq(SqList& L);

//��������Ԫ��e�����б������
Status Append_Sq(SqList& L, const void* e, size_t n);

//�������ڵ�iλǰ����һ��Ԫ��e��nΪԪ��e�Ŀռ��С
Status ListInsert_Sq(SqList& L, int i, const void* e, size_t n);

//���������б�������Ԫ��ɾ��������Ԫ��e
Status Remove_Sq(SqList& L, void* e);

//������ɾ�����е�i��Ԫ��
Status ListDelete_Sq(SqList& L, int i, void* e);

//��������ñ��е�i��Ԫ��
Status GetElem_Sq(SqList L, int i, void* e);

//�������޸ı��е�i��Ԫ��Ϊe��nΪԪ��e�Ŀռ��С
Status SetElem_Sq(SqList& L, int i, const void* e, size_t n);

//���������� ���Ը��Ӷ�������
Status ListTraverse_Sq(SqList L, Status(*visit)(const void*, void*), void* addition);
#endif // !__SQ_LIST_H__
