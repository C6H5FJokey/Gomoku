#ifndef __SHOW_H__
#define __SHOW_H__

#include <Windows.h>

#define FRAMES_PRE_SEC 30

//չʾ����
void Show();

//��ʼ������
void InitShow();

//����չʾ����
void SetShow(void (*show)(HANDLE& sOut));

//Ĭ��show����
void DefaultShow(HANDLE& sOut);
#endif // !__SHOW_H__
