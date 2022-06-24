#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "LkList.h"

typedef struct {
	void (*onNotify)(const void*, int);//��֪ͨʱ�����ĺ���
}Observer;

typedef struct Subject{
	DuLkList observers_;
	void (*notify)(Subject* subject, const void*, int);
}Subject;

//��ʼ�����۲����
void InitSubject(Subject* subject, void (*notify)(Subject* subject, const void*, int));

//��ӹ۲���
void AddObserver(Subject* subject, Observer* observer);

//�Ƴ� ���� �۲���
void RemoveObserver(Subject* subject);


#endif //!__OBSERVER_H__