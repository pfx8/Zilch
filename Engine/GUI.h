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
#include "../GameObject/GameObject.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class GUI
{
private:
	char			mNewGameObjectName[20] = {""};			// �ő�19����

public:
	bool			mIsWireframe;

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
