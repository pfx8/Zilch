//*****************************************************************************
//
// コンソールウィンドウ処理 [Console.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Console
{
private:

public:
	BOOL isConsoleRun;	// コンソール実行するかどうかを判断
	bool isConsoleFront; // コンソールとゲームウィンドウの前後判断

	Console();
	~Console();

	HRESULT SetConsoleBack(HWND hwnd, int cmd);		// コンソールからゲームウインドに戻る
	HRESULT SetConsoleFront(HWND hwnd);	// ゲームのウィンドからコンソールに変更
};


#endif // !_CONSOLE_H_
