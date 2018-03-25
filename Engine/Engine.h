//*****************************************************************************
//
// エンジンコアファイル [Engine.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止

#ifndef _ENGINE_H_
#define _ENGINE_H_

//*****************************************************************************
//
// ヘッドファイル
//
//*****************************************************************************
// DirectX9.0 and Windows
#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h>
#include <dinput.h>

// c++
#include <iostream>
#include <string>
#include <vector>
#include <map>

// 自作ヘッドファイル
#include "Camera.h"
#include "Console.h"
#include "DebugMessage.h"
#include "input.h"
#include "Light.h"
#include "Material.h"
#include "Plane.h"
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "Shader.h"
#include "SkyBox.h"
#include "Sound.h"
#include "StateMachine.h"
#include "StateMachineManager.h"

#include "..\GameObject\GameObject.h"
#include "..\Component\Component.h"

//*****************************************************************************
//
// 依存ファイル
//
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dsound.lib" )
#pragma comment (lib, "winmm.lib")

#endif

//*****************************************************************************
//
// マクロ定義
//
//*****************************************************************************
#define CLASS_NAME		_T("D3d9Class")		// ウインドウのクラス名
#define WINDOW_NAME		_T("Project : Zilch")		// ウインドウのキャプション名
#define SCREEN_WIDTH		(960)				// ウインドウの幅
#define SCREEN_HEIGHT		(540)				// ウインドウの高さ

#define RELEASE_POINT(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }
#define RELEASE_CLASS_POINT(ptr)			{ if(ptr) { delete ptr; } }
#define RELEASE_CLASS_ARRY_POINT(ptr)		{ if(ptr) { delete [] ptr;} }

#define	FVF_DX_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_DIFFUSE)
// 頂点フォーマット
typedef struct DX_VERTEX_3D
{
	// 頂点楮体変数の順番は頂点フォーマットのと同じ
	D3DXVECTOR4 position;		// 頂点座標
	D3DCOLOR diffuse;			// 反射光
}DX_VERTEX_3D;

//*****************************************************************************
//
// 構造体定義
//
//*****************************************************************************
// テクスチャ構造体
typedef struct TextureStruct
{
	const char*			Name;			// テクスチャ名前
	const char*			Path;			// テクスチャパス
	LPDIRECT3DTEXTURE9		TexturePoint;		// テクスチャポインタ
}TextureStruct;

//*****************************************************************************
//
// 列挙体定義
//
//*****************************************************************************
enum RenderStatus
{
	RS_withoutLight,
	RS_withLight,
	RS_withNormalMap,
};

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);

#endif // !_ENGINE_H_