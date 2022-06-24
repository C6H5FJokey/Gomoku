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


//函数：初始化一个链表，实际上就是创建一个头结点
Status InitList_DuL(DuLkList& L);

//函数：清空一个链表
Status ClearList_DuL(DuLkList& L);

//函数：销毁一个链表
Status DestroyList_DuL(DuLkList& L);

//函数：返回p指示线性表L中第i个节点并返回OK,i值不合法时返回ERROR
Status LocatePos_DuL(DuLkList L, int i, DuLNode*& p);

//函数：将元素e插在列表最前面
Status InsFirst_DuL(DuLkList& L, const void* e, size_t n);

//函数：将元素e插在列表最后面
Status Append_DuL(DuLkList& L, const void* e, size_t n);

//函数：在第i位前插入一个元素e，n为元素e的空间大小
Status ListInsert_DuL(DuLkList& L, int i, const void* e, size_t n);

//函数：将列表最前面的元素删除并返回元素e
Status DelFirst_DuL(DuLkList& L, void* e);

//函数：将列表最后面的元素删除并返回元素e
Status Remove_DuL(DuLkList& L, void* e);

Status ListDelete_DuL(DuLkList& L, int i, void* e);

//遍历整个表 可以附加额外数据
Status ListTraverse_DuL(DuLkList L, Status(*visit)(const void*, void*), void* addition);

#endif // !__LK_LIST_H__
