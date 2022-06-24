#ifndef __GAME_SHOW_H__
#define __GAME_SHOW_H__

#include <Windows.h>

void InitGameShow();//ÃÌº”π€≤Ï’ﬂ

void GameShow(HANDLE& sOut);

void PaintChessboard1(HANDLE& sOut);//1*1

void PaintPiece1(HANDLE& sOut);

void PaintCursor1(HANDLE& sOut);

void PaintUi1(HANDLE& sOut);

void PaintChessboard3(HANDLE& sOut);//3*3

void onNotifyMove(const void* object, int event);

#endif // !__GAME_SHOW_H__
