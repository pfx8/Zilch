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
#include "Shader.h"
#include "Model/Mesh.h"
#include "Model/Model.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Resources
{
private:

public:
	unordered_map<string, Model*>		mModels;		// モデル
	unordered_map<string, Texture*>		mTextures;		// テクスチャ
	unordered_map<string, Shader*>		mShaders;		// シェーダー

	Resources();
	~Resources();
	
	void createModel(string const path, enum MeshType type);		// モデルデータを作る
	Model* getModel(string name);									// モデルの名前によって取得
	void createTexture(string const path);							// テクスチャデータを作る
	Texture* getTexture(string name);								// テクスチャの名前によって取得
	void createShader(string const path);		// シェーダーデータを作る
	Shader* getShader(string techniqueName);						// シェーダーの名前によって取得
};

#endif // !_RESOURCES_H_

