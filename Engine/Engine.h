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
#include <unordered_map>				// mapが使われたところで、ペア関係だけできたっら順番にする必要がないのでmapからunordered_mapに変更した

using namespace std;

class Scene;
class GameObject;
class Component;
class Texture;
class Material;
class Mesh;
class Model;
class Resources;

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
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "fmod_vc.lib")	// fmod
#pragma comment (lib, "assimp-vc140-mt.lib")		// assimp
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

#define	FVF_DX_VERTEX_3D					(D3DFVF_XYZ | D3DFVF_DIFFUSE)

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

struct WorldVector
{
	// ゲーム世界の正方向ベクトルを初期化
	D3DXVECTOR3			worldLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3			worldUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3			worldRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
};

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
LPDIRECT3DDEVICE9 getD3DDevice(void);
Resources* getResources(void);
WorldVector getWorldVector(void);

#endif // !_ENGINE_H_