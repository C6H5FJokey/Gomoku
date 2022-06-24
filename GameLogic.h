#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include "CommonData.h"

typedef struct {
	Piece player;
	Point point;
}Unit;//ÿһ�εĲ���

enum class GameState
{
	MENU,
	LOOP,
	OVER
};

/*��ʼ����Ϸѭ������*/
void InitGameLoop();

/*��Ϸѭ������*/
void GameLoop();

/*��ʼ����Ϸ*/
void InitGame();

/*�������(x,y)λ��Ԫ��*/
Piece GetChessboardXY(int x, int y);

/*��õ�ǰ�����Ϣ*/
Unit GetCurrentPlayer();

/*���庯�� chessboardΪ���� unitΪһ��
* ����λ��û������ ��ɹ� ����ʧ��*/
Status FallPiece(Chessborad &chessboard, Unit unit);

/*���庯�� chessboardΪ���� unit�õ�������ǲ�
* �����Ի�����ɹ� ����ʧ��*/
Status UndoPiece(Chessborad& chessboard, Unit& unit);

/*�ж��������ߺ��� chessboardΪ���� unitΪһ��
* ������������ ��ɹ� ����ʧ��*/
Status PieceInLine(Chessborad chessboard, Unit unit);

/*��ȡ��ǰ��Ϸ״̬*/
GameState GetGameState();

/*��ȡʤ����*/
int GetWinCount(Piece player);

/*����ʤ����*/
void AddWinCount(Piece player);

#endif // !__GAME_LOGIC_H__
