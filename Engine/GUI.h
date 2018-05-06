//*****************************************************************************
//
// GUI処理[GUI.h]
//
// Author : LIAO HANCHEN
//
// ImGuiを利用してGUIを構築する
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
// クラス宣言
//
//*****************************************************************************
class GUI
{
private:
	char			mNewGameObjectName[20] = {""};			// 最大19文字

public:
	bool			mIsWireframe;

	GUI();
	~GUI();

	void start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice);		// ImGui初期化

	void draw();											// ImGuiの描画処理
	void systemGUI();										// システム操作GUI
	void sceneGUI();										// シーンGUI
	void createNewGameObjectGUI();							// 新しいGameObjectを作りメニュー
	
	bool IsAnyImguiFocused();								// ImGuiとアプリケーションの操作分離
};

#endif // !_GUI_H_
