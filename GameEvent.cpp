#include "GameEvent.h"
#include <stdlib.h>

static Subject* eventSubject;

void InitGameEvent() {
	eventSubject = (Subject*)malloc(sizeof(Subject));
	if (!eventSubject) exit(OVERFLOW);
	InitSubject(eventSubject, GameEventNotify);
}

//抛出唯一单例eventSubject
Subject* GetGameEventSubject() {
	return eventSubject;
}

typedef struct {
	void* object;
	int event;
}VisitPack;//给visit函数额外数据使用的结构体 局部使用 需要拆包

Status visit(const void* e, void* addition) {
	VisitPack* visitPack = (VisitPack*)addition;
	Observer* observer = (Observer*)e;
	observer->onNotify(visitPack->object, visitPack->event);
	return OK;
}

void GameEventNotify(Subject* subject, const void* object, int event) {
	VisitPack visitPack = {&object, event};
	ListTraverse_DuL(subject->observers_, visit, &visitPack);
}