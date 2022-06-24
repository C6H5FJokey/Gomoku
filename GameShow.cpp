#include "GameShow.h"
#include "GameLogic.h"
#include <wchar.h>
#include "Show.h"
#include "GameEvent.h"
#include <stdlib.h>

#define OVERFLOW -2

static int _cursorTime = 0;
static int _againFlickerTime = 0;

void InitGameShow()
{
	Observer* _moveObserver;
	_moveObserver = (Observer*)malloc(sizeof(Observer));
	if (!_moveObserver) exit(OVERFLOW);
	_moveObserver->onNotify = onNotifyMove;
	AddObserver(GetGameEventSubject(), _moveObserver);
}

void GameShow(HANDLE& sOut)
{
	PaintChessboard1(sOut);
	PaintPiece1(sOut);
	PaintUi1(sOut);
	switch (GetGameState())
	{
	case GameState::LOOP:
		PaintCursor1(sOut);
		break;
	case GameState::OVER:
		break;
	}
	
}

void PaintChessboard1(HANDLE& sOut)
{
	const wchar_t* chessboardChar[31] = {
		L"¨X ¨h ¨h ¨h ¨h ¨h ¨h ¨h ¨h ¨h ¨h ¨h ¨h ¨h ¨[ ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨c ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ©à ¨f ",
		L"¨^ ¨k ¨k ¨k ¨k ¨k ¨k ¨k ¨k ¨k ¨k ¨k ¨k ¨k ¨a ",
	};
	int i;
	DWORD recnum;
	COORD coord = { 0,0 };
	SetConsoleTextAttribute(sOut, FOREGROUND_GREEN);
	for (i = 0; i < 31; i++)
	{
		SetConsoleCursorPosition(sOut, coord);
		WriteConsole(sOut, chessboardChar[i], 30, &recnum, NULL);
		coord.Y++;
	}
}

void PaintPiece1(HANDLE& sOut)
{
	const wchar_t* pieceBlack = L"¡ð";
	const wchar_t* pieceWhite = L"¡ñ";
	int i, j;
	DWORD recnum;
	COORD coord = { 0,0 };
	SetConsoleTextAttribute(sOut, FOREGROUND_GREEN);
	for (i = 0; i < MAX_SIZE; i++)
	{
		for (j = 0; j < MAX_SIZE; j++) {
			if (GetChessboardXY(j, i) != Piece::NONE) {
				coord.X = j * 2;
				coord.Y = i;
				SetConsoleCursorPosition(sOut, coord);
				if (GetChessboardXY(j, i) == Piece::BLACK) WriteConsole(sOut, pieceBlack, 1, &recnum, NULL);
				if (GetChessboardXY(j, i) == Piece::WHITE) WriteConsole(sOut, pieceWhite, 1, &recnum, NULL);
			}
		}
	}
}

void PaintCursor1(HANDLE& sOut)
{
	const wchar_t* pieceBlack = L"¡ñ";//È¡·´É«
	const wchar_t* pieceWhite = L"¡ð";
	const int cursorInterval = FRAMES_PRE_SEC/2;
	Unit player;
	DWORD recnum;
	COORD coord = { 0,0 }; 
	if (!_cursorTime)_cursorTime = cursorInterval * 2;
	if (_cursorTime-- <= cursorInterval) return;
	player = GetCurrentPlayer();
	coord.X = player.point.x*2;
	coord.Y = player.point.y;
	SetConsoleTextAttribute(sOut, BACKGROUND_GREEN);
	SetConsoleCursorPosition(sOut, coord);
	if (GetChessboardXY(player.point.x, player.point.y) != Piece::NONE) {
		WriteConsole(sOut, L"  ", 2, &recnum, NULL);
	}
	else
	{
		if (player.player == Piece::BLACK) WriteConsole(sOut, pieceBlack, 1, &recnum, NULL);
		if (player.player == Piece::WHITE) WriteConsole(sOut, pieceWhite, 1, &recnum, NULL);
	}
}

void PaintUi1(HANDLE& sOut)
{
	const wchar_t* uiChar[31] = {
		L"¨q ©¤ ©¤ ©¤ ©¤ ¨r ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"©¦         ©¦ ",
		L"¨t ©¤ ©¤ ©¤ ©¤ ¨s ",
	};
	const int cursorInterval = FRAMES_PRE_SEC / 2;
	int i,winCount;
	DWORD recnum;
	COORD coord = { 30,0 };
	wchar_t output[8];
	SetConsoleTextAttribute(sOut, FOREGROUND_GREEN);
	for (i = 0; i < 31; i++)
	{
		SetConsoleCursorPosition(sOut, coord);
		WriteConsole(sOut, uiChar[i], 12, &recnum, NULL);
		coord.Y++;
	}
	coord = { 33, 1 };
	SetConsoleCursorPosition(sOut, coord);
	WriteConsole(sOut, L"Scores", 6, &recnum, NULL);
	coord = { 32, 3 };
	winCount = GetWinCount(Piece::BLACK);
	wsprintf(output, L"P1¡ð¡ª%02d",winCount<=99?winCount:99);
	SetConsoleCursorPosition(sOut, coord);
	WriteConsole(sOut, output, 6, &recnum, NULL);
	coord = { 32, 5 };
	winCount = GetWinCount(Piece::WHITE);
	wsprintf(output, L"P2¡ñ¡ª%02d", winCount <= 99 ? winCount : 99);
	SetConsoleCursorPosition(sOut, coord);
	WriteConsole(sOut, output, 6, &recnum, NULL);
	if (GetGameState() == GameState::OVER) {
		coord = { 32, 8 };
		SetConsoleCursorPosition(sOut, coord);
		WriteConsole(sOut, L"GAMEOVER", 8, &recnum, NULL);
		coord = { 33, 10 };
		SetConsoleCursorPosition(sOut, coord);
		WriteConsole(sOut, L"WINNER", 6, &recnum, NULL);
		coord = { 34, 11 };
		SetConsoleCursorPosition(sOut, coord);
		switch (GetCurrentPlayer().player)
		{
		case Piece::BLACK:
			WriteConsole(sOut, L"P1¡ð", 3, &recnum, NULL);
			SetConsoleTextAttribute(sOut, BACKGROUND_GREEN);
			coord = { 32, 3 };
			SetConsoleCursorPosition(sOut, coord);
			WriteConsole(sOut, L"P1¡ñ", 3, &recnum, NULL);
			break;
		case Piece::WHITE:
			WriteConsole(sOut, L"P2¡ñ", 3, &recnum, NULL);
			SetConsoleTextAttribute(sOut, BACKGROUND_GREEN);
			coord = { 32, 5 };
			SetConsoleCursorPosition(sOut, coord);
			WriteConsole(sOut, L"P2¡ð", 3, &recnum, NULL);
			break;
		}
		if (!_againFlickerTime)_againFlickerTime = cursorInterval * 2;
		if (_againFlickerTime-- > cursorInterval) {
			SetConsoleTextAttribute(sOut, FOREGROUND_GREEN);
		}
		coord = { 33, 13 };
		SetConsoleCursorPosition(sOut, coord);
		WriteConsole(sOut, L"AGAIN?", 6, &recnum, NULL);

	}
	else _againFlickerTime = 0;
}



void PaintChessboard3(HANDLE& sOut)
{
	const wchar_t* chessboardChar[46] = {
		L"                                                                                         ",
		L"  ¨X ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨h ¨T ¨T ¨[  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨c ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ©à ©¤ ©¤ ¨f  ",
		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",

		L"  ¨U     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ©¦     ¨U   ",
		L"  ¨^ ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨k ¨T ¨T ¨a  ",
		L"                                                                                         "
	};
	int i;
	DWORD recnum;
	COORD coord = {0,0};
	SetConsoleTextAttribute(sOut, FOREGROUND_GREEN);
	for (i = 0; i < 46; i++)
	{
		SetConsoleCursorPosition(sOut, coord);
		WriteConsole(sOut, chessboardChar[i], 90, &recnum, NULL);
		coord.Y++;
	}
}

void onNotifyMove(const void* object, int event) {
	_cursorTime = 0;
}