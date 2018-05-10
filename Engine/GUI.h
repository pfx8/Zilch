//*****************************************************************************
//
// GUI����[GUI.h]
//
// Author : LIAO HANCHEN
//
// ImGui�𗘗p����GUI���\�z����
// 
//****************************************************************************
#ifndef _GUI_H_
#define _GUI_H_

#include "Engine.h"
#include "GameTimes.h"
#include "SceneManager.h"

#include "GameObject/GameObject.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class GUI
{
private:
	bool				mIsWireframe;							// ���C���t���[���`�F�b�N
	char				mNewGameObjectName[20] {" "};			// �ő�19����

	const char*			mColorRamp[2] {u8"���j�A", u8"���"};
	const char*			mShadingMode[4] {u8"�f�B�t���[�Y", u8"�m�[�}��", u8"�e�N�X�`���F", u8"�V�F�[�f�B���O"};

public:

	GUI();
	~GUI();

	void start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice);		// ImGui������

	void draw();											// ImGui�̕`�揈��
	void systemGUI();										// �V�X�e������GUI
	void sceneGUI();										// �V�[��GUI
	void createNewGameObjectGUI();							// �V����GameObject����胁�j���[
	
	bool IsAnyImguiFocused();								// ImGui�ƃA�v���P�[�V�����̑��앪��
};

#endif // !_GUI_H_
