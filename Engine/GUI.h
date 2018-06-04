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
#include "Shader.h"

#include "..\Component\Light.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class GUI
{
private:
	bool				mIsWireframe;
	char				mNewGameObjectName[20] = { NULL };		// GameObjectの名前は最大19文字

	const char*			mColorRamp[2] = { u8"リニア", u8"一定" };
	ColorRamp			mCurrentColorRampType;
	const char*			mRenderingMode[5] = { u8"テクスチャ色", u8"ディフューズ", u8"スペキュラー", u8"ノーマル", u8"シェーディング" };
	RenderingMode		mCurrentRenderingMode;
	const char*			mLanguage[2] = { u8"日本語", u8"English" };
	int					mCurrentLanguage;

public:
	bool				mIsAddingModel;	
	bool				mIsModelFile;
	wstring				mAddingFilePath = { L" " };				// ドロップされたファイルのパスを保存

	GUI(void);
	~GUI(void);

	void start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice);

	void draw(void);
	void systemGUI(void);
	void sceneGUI(void);
	void createNewGameObjectGUI(void);
	void addModelImGui(void);
	void dropFileErrorGUI(void);

	bool isAnyImGuiFocused(void);
	bool isGameObjectNameRight(wstring name);
};

#endif // !_GUI_H_
