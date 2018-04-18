﻿//*****************************************************************************
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
//*****************************************************************************
void Resources::loadShader(string name, string path)
{
	mShaders.insert({ name, new Shader(path) });
}

//*****************************************************************************
//
// シェーダーの名前によって取得
//
//*****************************************************************************
Shader* Resources::getShader(string name)
{
	if (mShaders.find(name) != mShaders.end())
	{
		return mShaders[name];
	}
	cout << "[Error] <Shader> Get " << name << " ... failed!" << endl;
	return nullptr;
}