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
	map < string, string> textures;
	string GetTextureStruct(string name);		// テクスチャパスを取得

	// メッシュ
	map < string, string> meshes;
	string GetMeshPath(string name);		// メッシュパスを取得	

	// モデル
	map<string, Model*> models;

public:
	ResourcesManager();
	~ResourcesManager();

	HRESULT LoadTexture(string name, LPDIRECT3DTEXTURE9* texturePoint);	// テクスチャを読み込み
	HRESULT LoadModel(string name, Model* model);						// モデルを読み込み
	
	void LoadModel(string name, const char *path);						// Assimpでモデルを読み込み
	Model *GetModel(string name);										// モデルを名前によってゲット
};

#endif // !_RESOURCES_MANAGER_H_

