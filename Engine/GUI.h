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

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class GUI
{
private:

public:
	bool		isWireframe;

	GUI();
	~GUI();

	void start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice);		// ImGui������
	void draw();											// ImGui�̕`�揈��
	void systemGUI();										// �V�X�e������GUI
	void sceneGUI();										// �V�[��GUI
};

#endif // !_GUI_H_
