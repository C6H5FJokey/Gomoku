#ifndef __USER_INPUT_H__
#define __USER_INPUT_H__

#include "CommonData.h"

/*输入的内部循环逻辑
*/
void ProcessInput();

/*判定玩家输入方向 
* 返回方向*/
Direction Move();

/*判定玩家是否按下确认
* 按下为true 否则为false*/
Status IsConfirming();

/*判定玩家是否按下撤销
* 按下为true 否则为false*/
Status IsUndoing();

#endif // !__USER_INPUT_H__
