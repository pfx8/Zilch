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
void Resources::createModel(string const path, MeshType type)
{
	// パスからファイルの名前を取得(拡張子抜き)
	string name = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	name = name.substr(0, name.find_first_of("."));									// exp: ccc.fbx -> ccc

	// モデルデータを保存
	mModels.insert({ name, new Model(type, name, path) });
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
void Resources::createTexture(string const path)
{
	// パスからファイルの名前を取得(拡張子抜き)
	string name = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	name = name.substr(0, name.find_first_of("."));									// exp: ccc.fbx -> ccc

	mTextures.insert({ name, new Texture(name, path) });	
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
void Resources::createShader(string const path)
{
	// パスからファイルの名前を取得(拡張子抜き)
	string techniqueName = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	techniqueName = techniqueName.substr(0, techniqueName.find_first_of("."));					// exp: ccc.fbx -> ccc

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
Shader* Resources::getShader(string techniqueName)
{
	if (mShaders.find(techniqueName) != mShaders.end())
	{
		return mShaders[techniqueName];
	}

	cout << "[Error] <Shader> Get technique " << techniqueName << " ... failed!" << endl;
	return nullptr;
}