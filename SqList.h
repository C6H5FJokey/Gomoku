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


//函数：初始化一个链表，实际上就是创建一个头结点
Status InitList_Sq(SqList& L);

//函数：清空一个链表
Status ClearList_Sq(SqList& L);

//函数：销毁一个链表
Status DestroyList_Sq(SqList& L);

//函数：将元素e插在列表最后面
Status Append_Sq(SqList& L, const void* e, size_t n);

//函数：在第i位前插入一个元素e，n为元素e的空间大小
Status ListInsert_Sq(SqList& L, int i, const void* e, size_t n);

//函数：将列表最后面的元素删除并返回元素e
Status Remove_Sq(SqList& L, void* e);

//函数：删除表中第i个元素
Status ListDelete_Sq(SqList& L, int i, void* e);

//函数：获得表中第i个元素
Status GetElem_Sq(SqList L, int i, void* e);

//函数：修改表中第i个元素为e，n为元素e的空间大小
Status SetElem_Sq(SqList& L, int i, const void* e, size_t n);

//遍历整个表 可以附加额外数据
Status ListTraverse_Sq(SqList L, Status(*visit)(const void*, void*), void* addition);
#endif // !__SQ_LIST_H__
