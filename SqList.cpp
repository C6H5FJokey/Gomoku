#include "SqList.h"
#include <stdlib.h>
#include <string.h>

Status InitList_Sq(SqList& L)
{
    L.elem = (SqNode*)malloc(LIST_INIT_SIZE * sizeof(void*));
    if (!L.elem)exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status ClearList_Sq(SqList& L)
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        free(L.elem[i].data);
        L.elem[i].data = NULL;
        L.elem[i].n = 0;
    }
    L.length = 0;
    return OK;
}

Status DestroyList_Sq(SqList& L)
{
    ClearList_Sq(L);
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

Status Append_Sq(SqList& L, const void* e, size_t n)
{
    SqNode* newbase;
    char* buffer;
    if (L.length >= L.listsize) {
        newbase = (SqNode*)realloc(L.elem, sizeof(void*) * L.listsize * 2);
        if (!newbase) exit(OVERFLOW);
        L.elem = newbase;
        L.listsize *= 2;
    }
    buffer = (char*)malloc(n);
    if (!buffer)exit(OVERFLOW);
    memcpy(buffer, e, n);
    L.elem[L.length].data = buffer;
    L.elem[L.length].n = n;
    L.length++;
    return OK;
}

Status ListInsert_Sq(SqList& L, int i, const void* e, size_t n)
{
    SqNode* newbase;
    SqNode* p;
    SqNode* q;
    char* buffer;
    if (i < 1 || i > L.length + 1)return ERROR;
    if (L.length >= L.listsize) {
        newbase = (SqNode*)realloc(L.elem, sizeof(void*) * L.listsize * 2);
        if (!newbase) exit(OVERFLOW);
        L.elem = newbase;
        L.listsize *= 2;
    }
    buffer = (char*)malloc(n);
    if (!buffer)exit(OVERFLOW);
    memcpy(buffer, e, n);
    q = &(L.elem[i - 1]);
    for (p = &(L.elem[L.length - 1]); p >= q; --p)*(p + 1) = *p;
    q->data = buffer;
    q->n = n;
    L.length++;
    return OK;
}

Status Remove_Sq(SqList& L, void* e)
{
    memcpy(e, L.elem[L.length].data, L.elem[L.length].n);
    free(L.elem[L.length].data);
    L.elem[L.length].data = NULL;
    L.elem[L.length].n = 0;
    L.length--;
    return OK;
}

Status ListDelete_Sq(SqList& L, int i, void* e)
{
    SqNode* p;
    SqNode* q;
    if (i<1 || i > L.length) return ERROR;
    p = &(L.elem[i - 1]);
    memcpy(e, p->data, p->n);
    free(p->data);
    q = L.elem + L.length - 1;
    for (++p; p <= q; ++p) *(p - 1) = *p;
    q->data = NULL;
    q->n = 0;
    L.length--;
    return OK;
}

Status GetElem_Sq(SqList L, int i, void* e)
{
    if (i<1 || i > L.length) return ERROR;
    memcpy(e, L.elem[i].data, L.elem[i].n);
    return OK;
}

Status SetElem_Sq(SqList& L, int i, const void* e, size_t n)
{
    char* buffer;
    if (i<1 || i > L.length) return ERROR;
    if (L.elem[i-1].n == n) 
    {
        buffer = (char*)L.elem[i-1].data;
    }
    else
    {
        buffer = (char*)malloc(n);
        if (!buffer)exit(OVERFLOW);
        free(L.elem[i-1].data);
        L.elem[i-1].n = n;
    }
    memcpy(buffer, e, n);
    L.elem[i-1].data = buffer;
    return OK;
}

Status ListTraverse_Sq(SqList L, Status(*visit)(const void*, void*), void* addition)
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (!visit(L.elem[i].data, addition)) return ERROR;
    }
    return OK;
}
