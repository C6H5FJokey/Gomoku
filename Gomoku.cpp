#ifndef _DEBUG

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

#else

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "UserInput.h"
#include "GameLogic.h"
#include "Show.h"
#include "GameShow.h"
#include "GameEvent.h"

int main() 
{
	/*time_t previous, current;
	int x = 1;
	previous = current = time(NULL);*/
	//while (true)
	//{
	//	current = time(NULL);
	//	if (current - previous >= 1) {
	//		if (_kbhit()) {
	//			printf("2");
	//		}
	//		previous = current;
	//	}
	//	printf("%d ", _getch());

	/*while (true)
	{
		ProcessInput();
		if (Move() == Direction::LEFT)printf("left");
		if (IsConfirming()) printf("confirm");
		if (IsUndoing()) printf("undo");
	}*/

	/*InitGame();
	while (true)
	{
		ProcessInput();
		GameLoop();
		system("cls");
		for (int i = 0; i < MAX_SIZE; i++)
		{
			for (int j = 0; j < MAX_SIZE; j++) {
				switch (GetChessboardXY(j,i))
				{
				case Piece::BLACK:
					printf("1");
					break;
				case Piece::WHITE:
					printf("2");
					break;
				case Piece::NONE:
					printf("0");
				}
			}
			printf("\n");
		}
	}*/
	InitGameEvent();
	InitGameLoop();
	InitGame();
	InitShow();
	InitGameShow();
	SetShow(GameShow);
	while (true)
	{
		ProcessInput();
		GameLoop();
		Show();
	}
    return 0;
}

#endif // DEBUG