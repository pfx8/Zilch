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
	unordered_map<string, Model*>			mModels;		// モデル
	unordered_map<string, Texture*>			mTextures;		// テクスチャ
	unordered_map<string, Shader*>			mShaders;		// シェーダー

public:
	Resources();
	~Resources();
	
	void loadModel(string name, string path);		// Assimpでモデルを読み込み
	Model* getModel(string name);					// モデルの名前によって取得
	void loadTexture(string name, string path);		// テクスチャを読み込み
	Texture* getTexture(string name);				// テクスチャの名前によって取得
	void loadShader(string name, string path);		// シェーダーを読み込み
	Shader* getShader(string name);					// シェーダーの名前によって取得
};

#endif // !_RESOURCES_H_

