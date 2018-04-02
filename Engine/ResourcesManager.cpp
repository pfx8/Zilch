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
	else
	{
		cout << "[Error] " << name << " failed!" << endl;
		return nullptr;
	}
}

//*****************************************************************************
//
// Assimpでテクスチャを読み込み
//
//*****************************************************************************
void ResourcesManager::LoadTexture(string name, string path)
{
	Texture texture;
	texture.path = path;
	texture.type = " ";
	texture.point = nullptr;

	// テクスチャを読み込み
	if (FAILED(D3DXCreateTextureFromFile(
		mD3DDevice,
		path.c_str(),
		&texture.point)))
	{
		cout << "[Error] Loading <Texture> " << name << " ... Fail!" << endl;	// コンソールにメッセージを出す
	}
	else
	{
		cout << "[Information] Loading <Texture> " << name << " ... Success!" << endl;	// コンソールにメッセージを出す
	}
		
}

//*****************************************************************************
//
// テクスチャを名前によって取得
//
//*****************************************************************************
Texture* ResourcesManager::GetTexture(string name)
{

}