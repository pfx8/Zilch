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
void Resources::createModel(wstring name, const wstring path)
{
	// モデルデータを保存
	mModels.insert({ name, new Model(name, path) });
}

//*****************************************************************************
//
// モデルの名前によってゲット
//
//*****************************************************************************
Model* Resources::getModel(wstring name)
{
	if (mModels.find(name) != mModels.end())
	{
		return mModels[name];
	}

	// Debugウインドへ
	wcout << "<Error> get " << name << " ... failed!" << endl;

	return nullptr;
}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
void Resources::createTexture(const wstring path)
{
	// パスからファイルの名前を取得(拡張子抜き)
	wstring name = pathToFileName(path);

	mTextures.insert({ name, new Texture(name, path) });	
}

//*****************************************************************************
//
// テクスチャの名前によって取得
//
//*****************************************************************************
Texture* Resources::getTexture(wstring name)
{
	if (mTextures.find(name) != mTextures.end())
	{
		return mTextures[name];
	}

	// Debugウインドへ
	wcout << "<Error> get " << name << " ... failed!" << endl;

	return nullptr;
}

//*****************************************************************************
//
// シェーダーを読み込み
//
// 初期化した後でtechniqueを選択
//
//*****************************************************************************
void Resources::createShader(const wstring path)
{
	// パスからファイルの名前を取得(拡張子抜き)
	wstring techniqueName = pathToFileName(path);

	// シェーダーデータを作る
	Shader* shader = new Shader(path);
	
	// techniqueを確定
	shader->mEffect->SetTechnique((D3DXHANDLE)techniqueName.c_str());

	// 選択Mapに入れる
	mShaders.insert({ techniqueName, shader });
}

//*****************************************************************************
//
// シェーダーの名前によって取得
//
//*****************************************************************************
Shader* Resources::getShader(wstring techniqueName)
{
	if (mShaders.find(techniqueName) != mShaders.end())
	{
		return mShaders[techniqueName];
	}

	// Debugウインドへ
	wcout << "<Error> get technique " << techniqueName << " ... failed!" << endl;

	return nullptr;
}