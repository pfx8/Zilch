﻿//*****************************************************************************
//
// コンソール処理 [Console.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Console.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Console::Console(void)
{
	// コンソールを初期化
	this->mIsConsoleRun = AllocConsole();

	// コンソールのタイトルを設定する
	SetConsoleTitle(_T("Console"));

	// コンソールにinput,outputを指定
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Console::~Console(void)
{
	this->mIsConsoleRun = FreeConsole() & 1;
}

//*****************************************************************************
//
// コンソールからゲームウインドに戻る
//
//*****************************************************************************
HRESULT Console::SetConsoleBack(HWND hwnd, int cmd)
{
	return S_OK;
}

//*****************************************************************************
//
// ゲームのウィンドからコンソールに変更
//
//*****************************************************************************
HRESULT Console::SetConsoleFront(HWND hwnd)
{
	return S_OK;;
}