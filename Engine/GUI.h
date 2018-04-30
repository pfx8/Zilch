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

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class GUI
{
private:
	void start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice);		// ImGui初期化

public:
	GUI();
	~GUI();
};

#endif // !_GUI_H_
