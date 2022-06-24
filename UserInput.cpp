#include "UserInput.h"
#include <conio.h>
#include <ctype.h>
#include <stdio.h>

static int _input = 0;

void ProcessInput() {
	int key;
	if (!_kbhit()) {
		_input = 0;
		return;
	}
	key = _getch();
	if (key != 0 && key != 224 && key != 161) {
		_input = tolower(key);
		return;
	}
	key = _getch();
	_input = key;
	return;
}

Direction Move() {
	switch (_input)
	{
	case 'w':
	case 72:
		return Direction::UP;
	case 's':
	case 80:
		return Direction::DOWN;
	case 'a':
	case 75:
		return Direction::LEFT;
	case 'd':
	case 77:
		return Direction::RIGHT;
	default:
		return Direction::NONE;
	}
}

Status IsConfirming() {
	switch (_input)
	{
	case 13:
	case 32:
		return TRUE;
	default:
		return FALSE;
	}
}

Status IsUndoing() {
	switch (_input)
	{
	case 26:
	case 8:
		return TRUE;
	default:
		return FALSE;
	}
}