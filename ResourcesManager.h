//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include <map>

#include "Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class ResourcesManager
{
private:
	// テクスチャ
	std::map < std::string, std::string> m_textureList;	// テクスチャリスト
	std::string GetTextureStruct(std::string name);		// テクスチャパスを取得

	// Fbxファイル
	std::map < std::string, std::string> m_fbxList;	// Fbxリスト
public:
	ResourcesManager();
	~ResourcesManager();

	HRESULT LoadTexture(std::string name, LPDIRECT3DTEXTURE9* texturePoint);	// テクスチャを読み込み
	std::string GetFbxPath(std::string name);		// Fbxパスを取得
};

#endif // !_RESOURCES_MANAGER_H_

