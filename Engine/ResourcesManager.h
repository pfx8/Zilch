//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "Engine.h"
#include "..\Model\Mesh.h"
#include "..\Model\Model.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class ResourcesManager
{
private:
	// テクスチャ
	map < string, string> textureList;	// テクスチャリスト
	string GetTextureStruct(string name);		// テクスチャパスを取得

	// メッシュ
	map < string, string> meshList;	// メッシュリスト
	string GetMeshPath(string name);		// メッシュパスを取得	

public:
	ResourcesManager();
	~ResourcesManager();

	HRESULT LoadTexture(string name, LPDIRECT3DTEXTURE9* texturePoint);	// テクスチャを読み込み
	HRESULT LoadMesh(string name, Model* model);	// メッシュを読み込み
};

#endif // !_RESOURCES_MANAGER_H_

