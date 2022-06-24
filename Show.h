#ifndef __SHOW_H__
#define __SHOW_H__

#include <Windows.h>

#define FRAMES_PRE_SEC 30

//展示函数
void Show();

//初始化函数
void InitShow();

//设置展示函数
void SetShow(void (*show)(HANDLE& sOut));

//默认show函数
void DefaultShow(HANDLE& sOut);
#endif // !__SHOW_H__
