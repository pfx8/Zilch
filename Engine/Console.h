//*****************************************************************************
//
// �R���\�[���E�B���h�E���� [Console.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Console
{
private:

public:
	bool isConsoleRun;	// �R���\�[�����s���邩�ǂ����𔻒f
	bool isConsoleFront; // �R���\�[���ƃQ�[���E�B���h�E�̑O�㔻�f

	Console();
	~Console();

	HRESULT SetConsoleBack(HWND hwnd, int cmd);		// �R���\�[������Q�[���E�C���h�ɖ߂�
	HRESULT SetConsoleFront(HWND hwnd);	// �Q�[���̃E�B���h����R���\�[���ɕύX
};


#endif // !_CONSOLE_H_