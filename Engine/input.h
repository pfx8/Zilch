//*****************************************************************************
//
// ���͏��� [Input.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "Engine.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �v���O������������Ƃ��Ɏg��
#define	USE_KEYBOARD					// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define	USE_MOUSE						// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define	USE_PAD							// �錾����ƃp�b�h�ő���\�ɂȂ�

// �Q�[���p�b�h�̃{�^���ݒ�
#define LEFT_STICK_UP			0x00000001l			// ���X�e�B�b�N��(.IY<0)
#define LEFT_STICK_DOWN			0x00000002l			// ���X�e�B�b�N��(.IY>0)
#define LEFT_STICK_LEFT			0x00000004l			// ���X�e�B�b�N��(.IX<0)
#define LEFT_STICK_RIGHT		0x00000008l			// ���X�e�B�b�N�E(.IX>0)
#define BUTTON_SQUARE			0x00000010l			// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_CROSS			0x00000020l			// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_CIRCLE			0x00000040l			// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_TRIANGLE			0x00000080l			// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_L1				0x00000100l			// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_R1				0x00000200l			// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L2				0x00000400l			// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R2				0x00000800l			// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_SHARE			0x00001000l			// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_OPTIONS			0x00002000l			// �l�{�^��(.rgbButtons[9]&0x80)
#define RIGHT_STICK_UP			0x00004000l			// �E�X�e�B�b�N��(.Z��]<0)
#define RIGHT_STICK_DOWN		0x00008000l			// �E�X�e�B�b�N��(.Z��]>0)
#define RIGHT_STICK_LEFT		0x00010000l			// �E�X�e�B�b�N��(.IZ<0)
#define RIGHT_STICK_RIGHT		0x00020000l			// �E�X�e�B�b�N�E(.IZ>0)

#define GAMEPADMAX				4					// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);		// ���̓f�o�C�X�̏�����
void UpdateInput(void);								// ���̓f�o�C�X�̍X�V����
void UninitInput(void);								// ���̓f�o�C�X�̏I������

//*****************************************************************************
//
// �L�[�{�[�h����
//
//*****************************************************************************
bool GetKeyboardPress(int nKey);			// �L�[�{�[�h�̃v���X��Ԃ��擾
bool GetKeyboardTrigger(int nKey);			// �L�[�{�[�h�̃g���K�[��Ԃ��擾
bool GetKeyboardRepeat(int nKey);			// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
bool GetKeyboardRelease(int nKey);			// �L�[�{�[�h�̃����|�X��Ԃ��擾

//*****************************************************************************
//
// �}�E�X����
//
//*****************************************************************************
BOOL IsMouseLeftPressed(void);		// ���N���b�N������Ԃ��擾
BOOL IsMouseLeftTriggered(void);	// ���N���b�N�����u�Ԃ��`�F�b�N
BOOL IsMouseRightPressed(void);		// �E�N���b�N������Ԃ��擾
BOOL IsMouseRightTriggered(void);	// �E�N���b�N�����u�Ԃ��`�F�b�N
BOOL IsMouseCenterPressed(void);	// ���N���b�N������Ԃ��擾
BOOL IsMouseCenterTriggered(void);	// ���N���b�N�����u�Ԃ��`�F�b�N
long GetMouseX(void);				// �}�E�X�����E�ɓ��������Βl
long GetMouseY(void);				// �}�E�X���O��ɓ��������Βl
long GetMouseZ(void);				// �}�E�X�z�C�[�������������Βl

//*****************************************************************************
//
// �Q�[���p�b�h����
//
//*****************************************************************************
BOOL IsButtonPressed(int padNo,DWORD button);		// �Q�[���p�b�h�̃{�^������������Ԃ��擾
BOOL IsButtonTriggered(int padNo,DWORD button);		// �Q�[���p�b�h�̃{�^�����������u�Ԃ��`�F�b�N

#endif