#ifndef __USER_INPUT_H__
#define __USER_INPUT_H__

#include "CommonData.h"

/*������ڲ�ѭ���߼�
*/
void ProcessInput();

/*�ж�������뷽�� 
* ���ط���*/
Direction Move();

/*�ж�����Ƿ���ȷ��
* ����Ϊtrue ����Ϊfalse*/
Status IsConfirming();

/*�ж�����Ƿ��³���
* ����Ϊtrue ����Ϊfalse*/
Status IsUndoing();

#endif // !__USER_INPUT_H__
