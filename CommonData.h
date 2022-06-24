#ifndef __COMMON_DATA_H__
#define __COMMON_DATA_H__

#define MAX_SIZE 15 //���̵����ֵ
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;

enum class Piece{
	NONE,
	BLACK,
	WHITE
};//����

typedef Piece Chessborad[MAX_SIZE][MAX_SIZE];

typedef struct {
	int x;
	int y;
}Point;

enum class Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};//�ƶ�����
#endif // !__COMMON_DATA_H__
