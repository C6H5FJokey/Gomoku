#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include "CommonData.h"
#include "SqList.h"

typedef SqList Chessborad;

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

enum class MenuOption
{
	PLAY,
	EXIT
};

/*��ʼ����Ϸѭ������*/
void InitGameLoop();

/*��Ϸѭ������*/
void GameLoop();

/*��ʼ����Ϸ*/
void InitGame();

/*�������(x,y)λ��Ԫ�� x=1..15 y=1..15*/
Piece GetChessboardXY(int x, int y);

/*��������(x,y)λ��Ԫ�� x=0..14 y=0..14 ��������ѭ��*/
static void SetChessboardXY(int x, int y, Piece piece);

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

/*���ʤ����*/
static void ClearWinCount();

/*��ò˵���ǰѡ��*/
MenuOption GetMenuOption();

/*���ʤ������Ϣ*/
Piece GetWinner();

#endif // !__GAME_LOGIC_H__
