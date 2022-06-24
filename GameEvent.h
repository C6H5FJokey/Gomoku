#ifndef __GAME_EVENT_H__
#define __GAME_EVENT_H__

#include "Observer.h"

enum class GameEvent
{
	ERROR_FALL,//错误落棋
	PIECE_IN_LINE,//五子连线
	UNDO,//撤销
	MOVE,//移动
	EXIT//退出
};//一些事件

//游戏初始化调用
void InitGameEvent();

void GameEventNotify(Subject* subject, const void* object, int event);

//抛出唯一单例subject
Subject* GetGameEventSubject();

#endif // !__GAME_EVENT_H__
