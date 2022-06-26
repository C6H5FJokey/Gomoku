#ifndef __GAME_SHOW_H__
#define __GAME_SHOW_H__

#include <Windows.h>

void InitGameShow();//ÃÌº”π€≤Ï’ﬂ

void GameShow(HANDLE& sOut);

static void PaintChessboard1(HANDLE& sOut);//1*1

static void PaintPiece1(HANDLE& sOut);

static void PaintCursor1(HANDLE& sOut);

static void PaintUi1(HANDLE& sOut);

static void PaintUi1_frame(HANDLE& sOut);

static void PaintUi1_scores(HANDLE& sOut);

static void PaintUi1_end(HANDLE& sOut);

static void PaintUi1_menu(HANDLE& sOut);

static void PaintChessboard3(HANDLE& sOut);//3*3

static void onNotifyMove(const void* object, int event);

static void onNotifyPieceInLine(const void* object, int event);

static void onNotifyDeadlock(const void* object, int event);

#endif // !__GAME_SHOW_H__
