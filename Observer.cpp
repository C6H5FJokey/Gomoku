#include "Observer.h"

void InitSubject(Subject* subject, void (*notify)(Subject* subject ,const void*, int)) {

	InitList_DuL(subject->observers_);
	subject->notify = notify;
}

void AddObserver(Subject* subject, Observer* observer) {
	Append_DuL(subject->observers_, observer, sizeof(observer));
}

void RemoveObserver(Subject* subject) {
	ClearList_DuL(subject->observers_);
}