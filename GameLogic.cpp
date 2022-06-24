#include "GameLogic.h"
#include "LkStack.h"
#include "UserInput.h"
#include "Observer.h"
#include "GameEvent.h"
#include <stdlib.h>

static Chessborad _chessboard;
static Unit* _player;
static Unit* _otherPlayer;
static Unit* _tempPlayer;
static LkStack _execution;
static Subject* _subject;
static GameState _state;
static MenuOption _menuOption;
static int _winCount[2];

void InitGameLoop() {
	InitStack_Lk(_execution);
	_subject = GetGameEventSubject();
	_player = (Unit*)malloc(sizeof(Unit));
	if (!_player)exit(OVERFLOW);
	_otherPlayer = (Unit*)malloc(sizeof(Unit));
	if (!_otherPlayer)exit(OVERFLOW);
	_state = GameState::MENU;
	_menuOption = MenuOption::PLAY;
	_winCount[0] = 0;
	_winCount[1] = 0;
}

void InitGame() {
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++) {
			_chessboard[i][j] = Piece::NONE;
		}
	}
	*_player = {
		Piece::BLACK,
		{MAX_SIZE / 2, MAX_SIZE / 2}
	};
	
	*_otherPlayer = {
		Piece::WHITE,
		{MAX_SIZE / 2, MAX_SIZE / 2}
	};
	ClearStack_Lk(_execution);
}

void GameLoop() {
	switch (_state)
	{
	case GameState::MENU:
		switch (_menuOption)
		{
		case MenuOption::PLAY:
			switch (Move())
			{
			case Direction::UP:
				_menuOption = MenuOption::EXIT;
				break;
			case Direction::DOWN:
				_menuOption = MenuOption::EXIT;
				break;
			}
			if (IsConfirming())
			{
				InitGame();
				_state = GameState::LOOP;
			}
			break;
		case MenuOption::EXIT:
			switch (Move())
			{
			case Direction::UP:
				_menuOption = MenuOption::PLAY;
			case Direction::DOWN:
				_menuOption = MenuOption::PLAY;
			}
			if (IsConfirming())
			{
				GameEventNotify(_subject, _player, (int)GameEvent::EXIT);
				exit(0);
			}
			break;
		}
		break;
	case GameState::LOOP:
		switch (Move())
		{
		case Direction::UP:
			_player->point.y = (_player->point.y - 1 + MAX_SIZE) % MAX_SIZE;
			_subject->notify(_subject, _player, (int)GameEvent::MOVE);
			break;
		case Direction::DOWN:
			_player->point.y = (_player->point.y + 1) % MAX_SIZE;
			_subject->notify(_subject, _player, (int)GameEvent::MOVE);
			break;
		case Direction::LEFT:
			_player->point.x = (_player->point.x - 1 + MAX_SIZE) % MAX_SIZE;
			_subject->notify(_subject, _player, (int)GameEvent::MOVE);
			break;
		case Direction::RIGHT:
			_player->point.x = (_player->point.x + 1) % MAX_SIZE;
			_subject->notify(_subject, _player, (int)GameEvent::MOVE);
			break;
		}
		if (IsConfirming()) {
			if (FallPiece(_chessboard, *_player)) {
				if (PieceInLine(_chessboard, *_player)) {
					_subject->notify(_subject, _player, (int)GameEvent::PIECE_IN_LINE);
					_state = GameState::OVER;
					AddWinCount(_player->player);
				}
				else
				{
					_tempPlayer = _player; _player = _otherPlayer; _otherPlayer = _tempPlayer;//交换玩家
				}
			}
			else
			{
				_subject->notify(_subject, _player, (int)GameEvent::ERROR_FALL);
			}
		}
		if (IsUndoing()) {
			_tempPlayer = _player; _player = _otherPlayer; _otherPlayer = _tempPlayer;//交换玩家
			if (UndoPiece(_chessboard, *_player)) {
				_subject->notify(_subject, _player, (int)GameEvent::UNDO);
			}
			else
			{
				_tempPlayer = _player; _player = _otherPlayer; _otherPlayer = _tempPlayer;//交换玩家
			}
		}
		break;
	case GameState::OVER:
		if (IsConfirming()) {
			InitGame();
			_state = GameState::LOOP;
		}
		else if(IsUndoing())
		{

			_menuOption = MenuOption::PLAY;
			_state = GameState::MENU;
		}
		break;
	}
	
}

Status FallPiece(Chessborad& chessboard, Unit unit) {
	int x = unit.point.x;
	int y = unit.point.y;
	if (chessboard[y][x] != Piece::NONE) return FALSE;
	chessboard[y][x] = unit.player;
	Push_Lk(_execution, &unit, sizeof(unit));
	return TRUE;
}

Status UndoPiece(Chessborad& chessboard, Unit& unit) {
	int x, y;
	if (StackEmpty_Lk(_execution))return FALSE;
	Pop_Lk(_execution, &unit);
	x = unit.point.x;
	y = unit.point.y;
	chessboard[y][x] = Piece::NONE;
	return TRUE;
}

Status PieceInLine(Chessborad chessboard, Unit unit) {
	int x = unit.point.x;
	int y = unit.point.y;
	int count = 0;
	//横向搜索 先左后右
	while (--x >= 0 && chessboard[y][x] == unit.player) count++;
	x = unit.point.x;
	while (++x < MAX_SIZE && chessboard[y][x] == unit.player) count++;
	x = unit.point.x;
	if (count + 1 >= 5)return TRUE;//自己的位置要加上
	count = 0;//搜索失败 还原
	//纵向搜索 先上后下
	while (--y >= 0 && chessboard[y][x] == unit.player) count++;
	y = unit.point.y;
	while (++y < MAX_SIZE && chessboard[y][x] == unit.player) count++;
	y = unit.point.y;
	if (count + 1 >= 5)return TRUE;//自己的位置要加上
	count = 0;//搜索失败 还原
	//斜向搜索 先左上后右下
	while (--x >= 0 && --y >= 0 && chessboard[y][x] == unit.player) count++;
	x = unit.point.x;
	y = unit.point.y;
	while (++x < MAX_SIZE && ++y < MAX_SIZE && chessboard[y][x] == unit.player) count++;
	x = unit.point.x;
	y = unit.point.y;
	if (count + 1 >= 5)return TRUE;//自己的位置要加上
	count = 0;//搜索失败 还原
	//斜向搜索 先左下后右上
	while (--x >= 0 && ++y >= 0 && chessboard[y][x] == unit.player) count++;
	x = unit.point.x;
	y = unit.point.y;
	while (++x < MAX_SIZE && --y < MAX_SIZE && chessboard[y][x] == unit.player) count++;
	x = unit.point.x;
	y = unit.point.y;
	if (count + 1 >= 5)return TRUE;//自己的位置要加上
	return FALSE;//搜索失败
}

Piece GetChessboardXY(int x, int y) {
	return _chessboard[y][x];
}

Unit GetCurrentPlayer() {
	return *_player;
}

GameState GetGameState() {
	return _state;
}

int GetWinCount(Piece player) {
	switch (player)
	{
	case Piece::BLACK:
		return _winCount[0];
	case Piece::WHITE:
		return _winCount[1];
	default:
		return -1;
	}
}

void AddWinCount(Piece player) {
	switch (player)
	{
	case Piece::BLACK:
		_winCount[0]++;
		return;
	case Piece::WHITE:
		_winCount[1]++;
		return ;
	}
}

MenuOption GetMenuOption() 
{
	return _menuOption;
}