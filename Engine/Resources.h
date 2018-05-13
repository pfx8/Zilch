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

public:
	unordered_map<wstring, Model*>		mModels;		// モデル
	unordered_map<wstring, Texture*>	mTextures;		// テクスチャ
	unordered_map<wstring, Shader*>		mShaders;		// シェーダー

	Resources();
	~Resources();
	
	void createModel(const wstring path);				// モデルデータを作る
	Model* getModel(wstring name);						// モデルの名前によって取得
	void createTexture(const wstring path);				// テクスチャデータを作る
	Texture* getTexture(wstring name);					// テクスチャの名前によって取得
	void createShader(const wstring path);				// シェーダーデータを作る
	Shader* getShader(wstring techniqueName);			// シェーダーの名前によって取得
};

#endif // !_RESOURCES_H_

