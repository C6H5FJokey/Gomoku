#ifndef _DEBUG

#include "UserInput.h"
#include "GameLogic.h"
#include "Show.h"
#include "GameShow.h"
#include "GameEvent.h"

int main()
{
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
//#include "SqList.h"

Status visit1(const void* data, void* addition) {
	printf("%d ", *(int*)data);
	return OK;
}

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
	/*SqList L;
	int j;
	InitList_Sq(L);
	for (int i = 0; i < 11; i++) {
		Append_Sq(L, &i, sizeof(i));
	}
	ListTraverse_Sq(L, visit1, NULL);
	printf("\n");
	for (int i = 1; i <= 11 ; i++) {
		j = 11 - i;
		SetElem_Sq(L, i, &j, sizeof(j));
	}
	ListTraverse_Sq(L, visit1, NULL);*/
    return 0;

}

#endif // DEBUG