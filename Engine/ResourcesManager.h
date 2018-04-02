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
#include "Model\Mesh.h"
#include "Model\Model.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class ResourcesManager
{
private:
	map<string, Model*> mModels;
	map<string, Texture*> mTextures;

	LPDIRECT3DDEVICE9				mD3DDevice;		// D3Dデバイス

public:
	ResourcesManager();
	~ResourcesManager();
	
	void loadModel(string name, string path);					// Assimpでモデルを読み込み
	Model *GetModel(string name);								// モデルを名前によって取得
	void LoadTexture(string name, string path, TextureType type);					// Assimpでテクスチャを読み込み
	Texture *GetTexture(string name);							// テクスチャを名前によって取得
};

#endif // !_RESOURCES_MANAGER_H_

