//*****************************************************************************
//
// リソース管理 [Resources.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Resources.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Resources::Resources()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Resources::~Resources()
{
	// delete Map(to do)
}

//*****************************************************************************
//
// Assimpでモデルを読み込み
//
//*****************************************************************************
void Resources::loadModel(MeshType type, string name, string path)
{
	mModels.insert({ name, new Model(type, path) }); // モデルを名前とデータをペアにする
}

//*****************************************************************************
//
// モデルの名前によってゲット
//
//*****************************************************************************
Model* Resources::getModel(string name)
{
	if (mModels.find(name) != mModels.end())
	{
		return mModels[name];
	}
	cout << "[Error] <Model> Get " << name << " ... failed!" << endl;
	return nullptr;
}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
void Resources::loadTexture(string name, string path)
{
	mTextures.insert({ name, new Texture(path) });	
}

//*****************************************************************************
//
// テクスチャの名前によって取得
//
//*****************************************************************************
Texture* Resources::getTexture(string name)
{
	if (mTextures.find(name) != mTextures.end())
	{
		return mTextures[name];
	}
	cout << "[Error] <Texture> Get " << name << " ... failed!" << endl;
	return nullptr;
}

//*****************************************************************************
//
// シェーダーを読み込み
//
// 初期化した後でtechniqueを選択
// one shader one technique
//
//*****************************************************************************
void Resources::loadShader(string techniqueName, string path)
{
	Shader* shader = new Shader(path);
	
	// techniqueを確定
	shader->mEffect->SetTechnique((D3DXHANDLE)techniqueName.c_str());

	mShaders.insert({ techniqueName, shader });
}

//*****************************************************************************
//
// シェーダーの名前によって取得
//
//*****************************************************************************
Shader* Resources::getShader(string techniqueName)
{
	if (mShaders.find(techniqueName) != mShaders.end())
	{
		return mShaders[techniqueName];
	}
	cout << "[Error] <Shader> Get technique " << techniqueName << " ... failed!" << endl;
	return nullptr;
}