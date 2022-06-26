#include "Show.h"
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#define SWAY(a, b, type) {type temp = a;a = b;b = temp;}

static void (*_show)(HANDLE& _sOut);
static HANDLE _hOut;
static HANDLE _hIn;
static HANDLE _sOut;
static CONSOLE_SCREEN_BUFFER_INFO _cinfo;
static COORD _consoleSize = { 42,14 };
static clock_t _previous = 0, _current = 0;

void InitShow() {
	COORD size;
	CONSOLE_CURSOR_INFO cursorSetting;
	CONSOLE_FONT_INFOEX cfi = {};
	_hOut = GetStdHandle(STD_OUTPUT_HANDLE);;
	_hIn = GetStdHandle(STD_INPUT_HANDLE);
	_sOut = CreateConsoleScreenBuffer( GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (_sOut == INVALID_HANDLE_VALUE) {
		printf("缓冲区创建失败,错误号:%d", GetLastError());
		exit(1);
	}
	GetConsoleScreenBufferInfo(_hOut, &_cinfo);
	_cinfo.srWindow.Right = _consoleSize.X;
	_cinfo.srWindow.Bottom =_consoleSize.Y;
	SetConsoleWindowInfo(_hOut, TRUE, &_cinfo.srWindow);
	SetConsoleWindowInfo(_sOut, TRUE, &_cinfo.srWindow);
	size = { _consoleSize.X, _consoleSize.Y };
	size.X;
	size.Y;
	SetConsoleScreenBufferSize(_hOut, size);
	SetConsoleScreenBufferSize(_sOut, size);
	//隐藏光标
	cursorSetting = { 1,0 };
	SetConsoleCursorInfo(_hOut, &cursorSetting);
	SetConsoleCursorInfo(_sOut, &cursorSetting);
	//设置字体
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 40;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"新宋体");
	SetCurrentConsoleFontEx(_hOut, FALSE, &cfi);
	SetCurrentConsoleFontEx(_sOut, FALSE, &cfi);
	//设置默认函数
	_show = DefaultShow;
}

void SetShow(void (*show)(HANDLE& sOut)) {
	_show = show;
}

void Show() {
	DWORD recnum;
	//帧数限制
	_current = clock();
	if (_current - _previous < CLOCKS_PER_SEC / FRAMES_PRE_SEC) return;
	_previous = _current;
	//清屏函数
	FillConsoleOutputCharacter(_sOut, ' ', _cinfo.dwSize.X * _cinfo.dwSize.Y, { 0, 0 }, & recnum);//从{0,0}处开始填充' '字符,成功填充个数为recnum
	FillConsoleOutputAttribute(_sOut, 0, _cinfo.dwSize.X * _cinfo.dwSize.Y, { 0, 0 }, & recnum);
	//显示函数
	_show(_sOut);
	//显示缓冲区
	SetConsoleActiveScreenBuffer(_sOut);
	//交换缓冲区
	SWAY(_hOut, _sOut, HANDLE);
}

void DefaultShow(HANDLE& sOut) {
	DWORD recnum;
	//FillConsoleOutputCharacter(sOut, L'你', 1, { 0, 0 }, &recnum);
	//FillConsoleOutputAttribute(_sOut, FOREGROUND_GREEN, 20, { 0, 0 }, &recnum);
	SetConsoleCursorPosition(sOut, { 0, 0 });
	WriteConsole(sOut, L"◢██ ◣", 7, &recnum, NULL);
	SetConsoleCursorPosition(sOut, { 0, 1 });
	WriteConsole(sOut, L"███████", 7, &recnum, NULL);
	SetConsoleCursorPosition(sOut, { 0, 2 });
	WriteConsole(sOut, L"◥██ ◤", 7, &recnum, NULL);
}