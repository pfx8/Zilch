//*****************************************************************************
//
// リソース管理 [Resources.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "Engine.h"
#include "Model\Mesh.h"
#include "Model\Model.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Resources
{
private:
	map<string, Model*>				mModels;		// モデル
	map<string, Texture*>			mTextures;		// テクスチャ
	LPDIRECT3DDEVICE9				mD3DDevice;		// D3Dデバイス

public:
	Resources();
	~Resources();
	
	void loadModel(string name, string path);		// Assimpでモデルを読み込み
	Model *GetModel(string name);					// モデルを名前によって取得
	void LoadTexture(string name, string path);		// Assimpでテクスチャを読み込み
	Texture *GetTexture(string name);				// テクスチャを名前によって取得
};

#endif // !_RESOURCES_H_

