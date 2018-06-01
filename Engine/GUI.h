﻿//*****************************************************************************
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
	bool				mIsWireframe;							// ワイヤフレームチェック
	char				mNewGameObjectName[20] = { NULL };		// 最大19文字

	const char*			mColorRamp[2] = { u8"リニア", u8"一定" };
	ColorRamp			mCurrentColorRampType;
	const char*			mRenderingMode[5] = { u8"テクスチャ色", u8"ディフューズ", u8"スペキュラー", u8"ノーマル", u8"シェーディング" };
	RenderingMode		mCurrentRenderingMode;
	const char*			mLanguage[2] = { u8"日本語", u8"English" };
	int					mCurrentLanguage;

	vector<string>		mJapanese;
	vector<string>		mEnglish;

public:
	bool				mIsAddingModel;							// モデル読み込んでるをチェック
	bool				mIsModelFile;							// ドロップされたファイルが対象外エラー
	wstring				mAddingFilePath = { L" " };				// ドロップされたファイルのパスを保存

	GUI();
	~GUI();

	void start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice);		// ImGui初期化

	void draw();											// ImGuiの描画処理
	void systemGUI();										// システム操作GUI
	void sceneGUI();										// シーンGUI
	void createNewGameObjectGUI();							// 新しいGameObjectを作りメニュー
	
	bool isAnyImGuiFocused();								// ImGuiとアプリケーションの操作分離
	void addModelImGui();									// モデル追加GUI
	bool isGameObjectNameRight(wstring name);				// チェック追加GameObject名前
	void dropFileErrorGUI();								// ドロップされたファイルが対象外エラーGUI
};

#endif // !_GUI_H_
