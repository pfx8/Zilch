//*****************************************************************************
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
Console::Console()
{
	this->isConsoleRun = AllocConsole();	// コンソールを初期化
	SetConsoleTitle(_T("Debug Output"));	// コンソールのタイトルを設定する
	freopen("CONIN$", "r", stdin);	// コンソールにinput,outputを指定
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	this->isConsoleFront = false;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Console::~Console()
{
	this->isConsoleRun = FreeConsole() & 1;
}

//*****************************************************************************
//
// コンソールからゲームウインドに戻る
//
//*****************************************************************************
HRESULT Console::SetConsoleBack(HWND hwnd, int cmd)
{
		//ヴインドウを中心に移動
		RECT rect;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		MoveWindow(hwnd,
			(rect.right - rect.left - SCREEN_WIDTH) / 2,
			(rect.bottom - rect.top - SCREEN_HEIGHT) / 2,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			true);

		// ウインドウの表示(InitDiretX()の後に呼ばないと駄目)
		ShowWindow(hwnd, cmd);
		UpdateWindow(hwnd);

		this->isConsoleFront = false;

		return S_OK;
}

//*****************************************************************************
//
// ゲームのウィンドからコンソールに変更
//
//*****************************************************************************
HRESULT Console::SetConsoleFront(HWND hwnd)
{
	HWND consoleWindowHandle = GetConsoleWindow();

	if (consoleWindowHandle)
	{
		std::cout << "[State] Console is Top:" << std::endl;
		RECT rect;	//ヴインドウを中心に移動
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		SetWindowPos(consoleWindowHandle,
			hwnd,
			(rect.right - rect.left - SCREEN_WIDTH) / 2,
			(rect.bottom - rect.top - SCREEN_HEIGHT) / 2,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		ShowWindow(consoleWindowHandle, SW_NORMAL);
		UpdateWindow(consoleWindowHandle);

		this->isConsoleFront = true;

		return S_OK;
	}
	return E_FAIL;
}