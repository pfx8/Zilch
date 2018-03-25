//*****************************************************************************
//
// ���͏��� [Input.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "../Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class InputDevice
{
private:
	LPDIRECTINPUT8			input;
	LPDIRECTINPUTDEVICE8	keyBoard;
	LPDIRECTINPUTDEVICE8	gamePad;

public:
	InputDevice();
	~InputDevice();

	HRESULT InitInput(HINSTANCE hInst, HWND hWnd);		// ���̓f�o�C�X��������

	// �L�[�{�[�h
	HRESULT InitKeyBoard(HINSTANCE hInst, HWND hWnd);	// �L�[�{�[�h��������
	void 

	// �Q�[���p�b�h
	HRESULT InitGamePad();								// �Q�[���p�b�h��������

};

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �v���O������������Ƃ��Ɏg��
#define	USE_KEYBOARD										// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define	USE_MOUSE											// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define	USE_PAD												// �錾����ƃp�b�h�ő���\�ɂȂ�

// �����L�[��(.IY<0)
// �����L�[��(.IY>0)
// �����L�[��(.IX<0)
// �����L�[�E(.IX>0)

/* game pad��� */
#define LEFT_STICK_UP		0x00000001l	// ���X�e�B�b�N��(.IY<0)
#define LEFT_STICK_DOWN		0x00000002l	// ���X�e�B�b�N��(.IY>0)
#define LEFT_STICK_LEFT		0x00000004l	// ���X�e�B�b�N��(.IX<0)
#define LEFT_STICK_RIGHT	0x00000008l	// ���X�e�B�b�N�E(.IX>0)
#define BUTTON_SQUARE		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_CROSS		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_CIRCLE		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_TRIANGLE		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_L1			0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_R1			0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L2			0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R2			0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_SHARE		0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_OPTIONS		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)
#define RIGHT_STICK_UP		0x00004000l	// �E�X�e�B�b�N��(.Z��]<0)
#define RIGHT_STICK_DOWN	0x00008000l	// �E�X�e�B�b�N��(.Z��]>0)
#define RIGHT_STICK_LEFT	0x00010000l	// �E�X�e�B�b�N��(.IZ<0)
#define RIGHT_STICK_RIGHT	0x00020000l	// �E�X�e�B�b�N�E(.IZ>0)
#define GAMEPADMAX			4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
long GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
long GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
long GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl

//---------------------------- game pad
BOOL IsButtonPressed(int padNo,DWORD button);
BOOL IsButtonTriggered(int padNo,DWORD button);


#endif