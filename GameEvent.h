#ifndef __GAME_EVENT_H__
#define __GAME_EVENT_H__

#include "Observer.h"

enum class GameEvent
{
	ERROR_FALL,//��������
	PIECE_IN_LINE,//��������
	UNDO,//����
	MOVE,//�ƶ�
	EXIT//�˳�
};//һЩ�¼�

//��Ϸ��ʼ������
void InitGameEvent();

void GameEventNotify(Subject* subject, const void* object, int event);

//�׳�Ψһ����subject
Subject* GetGameEventSubject();

#endif // !__GAME_EVENT_H__
