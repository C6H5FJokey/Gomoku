#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "LkList.h"

typedef struct {
	void (*onNotify)(const void*, int);//被通知时触发的函数
}Observer;

typedef struct Subject{
	DuLkList observers_;
	void (*notify)(Subject* subject, const void*, int);
}Subject;

//初始化被观察对象
void InitSubject(Subject* subject, void (*notify)(Subject* subject, const void*, int));

//添加观察者
void AddObserver(Subject* subject, Observer* observer);

//移除 所有 观察者
void RemoveObserver(Subject* subject);


#endif //!__OBSERVER_H__