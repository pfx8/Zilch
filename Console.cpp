//*****************************************************************************
//
// �R���\�[������ [Console.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Console.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Console::Console()
{
	this->isConsoleRun = AllocConsole();	// �R���\�[����������
	SetConsoleTitle(_T("Debug Output"));	// �R���\�[���̃^�C�g����ݒ肷��
	freopen("CONIN$", "r", stdin);	// �R���\�[����input,output���w��
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	this->isConsoleFront = false;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Console::~Console()
{
	this->isConsoleRun = FreeConsole() & 1;
}

//*****************************************************************************
//
// �R���\�[������Q�[���E�C���h�ɖ߂�
//
//*****************************************************************************
HRESULT Console::SetConsoleBack(HWND hwnd, int cmd)
{
		//���C���h�E�𒆐S�Ɉړ�
		RECT rect;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
		MoveWindow(hwnd,
			(rect.right - rect.left - SCREEN_WIDTH) / 2,
			(rect.bottom - rect.top - SCREEN_HEIGHT) / 2,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			true);

		// �E�C���h�E�̕\��(InitDiretX()�̌�ɌĂ΂Ȃ��Ƒʖ�)
		ShowWindow(hwnd, cmd);
		UpdateWindow(hwnd);

		this->isConsoleFront = false;

		return S_OK;
}

//*****************************************************************************
//
// �Q�[���̃E�B���h����R���\�[���ɕύX
//
//*****************************************************************************
HRESULT Console::SetConsoleFront(HWND hwnd)
{
	HWND consoleWindowHandle = GetConsoleWindow();

	if (consoleWindowHandle)
	{
		std::cout << "[State] Console is Top:" << std::endl;
		RECT rect;	//���C���h�E�𒆐S�Ɉړ�
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