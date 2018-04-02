//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ResourcesManager.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ResourcesManager::ResourcesManager()
{
	mD3DDevice = GetDevice();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ResourcesManager::~ResourcesManager()
{
	RELEASE_POINT(mD3DDevice);

	// delete Map(to do)
}

//*****************************************************************************
//
// Assimpでモデルを読み込み
//
//*****************************************************************************
void ResourcesManager::loadModel(string name, string path)
{
	mModels.insert({ name, new Model(path) }); // モデルを名前とデータをペアにする
}

//*****************************************************************************
//
// モデルを名前によってゲット
//
//*****************************************************************************
Model* ResourcesManager::GetModel(string name)
{
	if (mModels.find(name) != mModels.end())
	{
		return mModels[name];
	}

	cout << "[Error] " << name << " failed!" << endl;
	return nullptr;
}

//*****************************************************************************
//
// Assimpでテクスチャを読み込み
//
//*****************************************************************************
void ResourcesManager::LoadTexture(string name, string path, TextureType type)
{
	mTextures.insert({ name, new Texture(path, type) });	
}

//*****************************************************************************
//
// テクスチャを名前によって取得
//
//*****************************************************************************
Texture* ResourcesManager::GetTexture(string name)
{
	if (mTextures.find(name) != mTextures.end())
	{
		return mTextures[name];
	}
	
	cout << "[Error] " << name << " failed!" << endl;
	return nullptr;
}