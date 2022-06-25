#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include "CommonData.h"
#include "SqList.h"

typedef SqList Chessborad;

typedef struct {
	Piece player;
	Point point;
}Unit;//每一次的操作

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

/*初始化游戏循环参数*/
void InitGameLoop();

/*游戏循环函数*/
void GameLoop();

/*初始化游戏*/
void InitGame();

/*获得棋盘(x,y)位置元素 x=1..15 y=1..15*/
Piece GetChessboardXY(int x, int y);

/*设置棋盘(x,y)位置元素 x=0..14 y=0..14 方便数组循环*/
static void SetChessboardXY(int x, int y, Piece piece);

/*获得当前玩家信息*/
Unit GetCurrentPlayer();

/*落棋函数 chessboard为棋盘 unit为一步
* 若该位置没有棋子 则成功 否则失败*/
Status FallPiece(Chessborad &chessboard, Unit unit);

/*悔棋函数 chessboard为棋盘 unit得到悔棋的那步
* 若可以悔棋则成功 否则失败*/
Status UndoPiece(Chessborad& chessboard, Unit& unit);

/*判定五子连线函数 chessboard为棋盘 unit为一步
* 若线上有五子 则成功 否则失败*/
Status PieceInLine(Chessborad chessboard, Unit unit);

/*获取当前游戏状态*/
GameState GetGameState();

/*获取胜利数*/
int GetWinCount(Piece player);

/*增加胜利数*/
void AddWinCount(Piece player);

/*清空胜利数*/
static void ClearWinCount();

/*获得菜单当前选项*/
MenuOption GetMenuOption();

#endif // !__GAME_LOGIC_H__
