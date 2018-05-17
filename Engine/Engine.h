//*****************************************************************************
//
// エンジンコアファイル [Engine.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

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
#include <Shlwapi.h>					// パスからファイルを探す

// c++
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <unordered_map>				// ペア関係だけで順番にする必要がないのでmapからunordered_mapに変更した
#include <typeindex>					// typeid()のため
#include <locale>

// Assimp
#include "..\FrameWork\assimp\include\assimp\Importer.hpp"
#include "..\FrameWork\assimp\include\assimp\scene.h"
#include "..\FrameWork\assimp\include\assimp\postprocess.h"

// FMOD
#include "..\FrameWork\FMOD\include\fmod.hpp"
#include "..\FrameWork\FMOD\include\fmod_errors.h"

// ImGui
#include "..\FrameWork\ImGui\imgui.h"
#include "..\FrameWork\ImGui\imgui_impl_dx9.h"
#include "..\FrameWork\ImGui\imgui_internal.h"

using namespace std;

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class GameObject;
class GUI;
class Scene;
class GameTimes;
class MeshRender;
class Component;
class Texture;
class Material;
class Bone;
class Mesh;
class Model;
class Resources;
class SceneManager;

//*****************************************************************************
//
// 依存lib
//
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Shlwapi.lib")										// PathFileExists()
#pragma comment (lib, "FrameWork/FMOD/lib/fmod_vc.lib")						// fmod
#pragma comment (lib, "FrameWork/assimp/lib/x86/assimp-vc140-mt.lib")		// assimp
#endif

//*****************************************************************************
//
// マクロ定義
//
//*****************************************************************************
#define CLASS_NAME							_T("D3d9Class")				// ウインドウのクラス名
#define WINDOW_NAME							_T("Project : Zilch")		// ウインドウのキャプション名
#define SCREEN_WIDTH						(1280)						// ウインドウの幅
#define SCREEN_HEIGHT						(720)						// ウインドウの高さ
#define NUM_BONES_PER_VEREX					(4)							// 頂点1個が影響される骨の最大数は4本

#define RELEASE_POINT(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }
#define RELEASE_CLASS_POINT(ptr)			{ if(ptr) { delete ptr; } }
#define RELEASE_CLASS_ARRY_POINT(ptr)		{ if(ptr) { delete [] ptr;} }

#define	FVF_DX_VERTEX_3D					(D3DFVF_XYZ | D3DFVF_DIFFUSE)

//*****************************************************************************
//
// 構造体定義
//
//*****************************************************************************
struct WorldVector
{
	// ゲーム世界の3軸
	D3DXVECTOR3		worldLook  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3		worldUp    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3		worldRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
};

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
// ローカル変数取得関数
LPDIRECT3DDEVICE9 getD3DDevice(void);
Resources* getResources(void);
GameTimes* getGameTimes(void);
SceneManager* getSceneManager(void);

// 文字列変換関数
string wStringToString(const wstring& ws);
wstring stringToWString(const string& s);

// 文字コード変換関数
string wstringUnicodeToUTF8(const wstring& ws);
wstring stringUTF8ToUnicode(const string& s);

// パスからファイル名を取得
wstring pathToFileName(const wstring path);

#endif // !_ENGINE_H_