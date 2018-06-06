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
Resources::Resources(void)
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Resources::~Resources(void)
{
	this->mModels.clear();
	this->mTextures.clear();
	this->mShaders.clear();
}

//*****************************************************************************
//
// Assimpでモデルを読み込み
//
//*****************************************************************************
void Resources::createModel(const wstring path)
{	
	// パスからファイルの名前を取得(拡張子抜き)
	wstring name = pathToFileName(path);
	mModels.insert({ name, new Model(path) });
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
void Resources::createTexture(wstring modelName, const wstring path, TexType type)
{
	// パスからファイルの名前を取得(拡張子抜き)
	// 同じ名前のテクスチャを防ぐために、テクスチャ名前の前にモデルの名前を付ける
	wstring name = modelName + pathToFileName(path);
	mTextures.insert({ name, new Texture(path, type) });	
}

//*****************************************************************************
//
// テクスチャの名前によって取得
//
//*****************************************************************************
Texture* Resources::getTexture(const wstring modelName, const wstring texName)
{
	wstring findName = modelName + texName;

	if (mTextures.find(findName) != mTextures.end())
	{
		return mTextures[findName];
	}

	// Debugウインドへ
	wcout << "<Error> get " << texName << " ... failed!" << endl;

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