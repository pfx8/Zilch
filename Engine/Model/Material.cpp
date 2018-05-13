﻿//*****************************************************************************
//
// マテリアル処理 [Material.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Material.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Material::Material(aiMaterial* mat)
{
	// デフォルト値
	this->mShininess = 1.0f;

	loadingMaterial(mat);
}

//*****************************************************************************
//
// マテリアルを読み込み
//
//*****************************************************************************
void Material::loadingMaterial(aiMaterial* mat)
{
	// マテリアルの名前を取得
	aiString name;
	mat->Get(AI_MATKEY_NAME, name);
	this->mName = stringUTF8ToUnicode(name.C_Str());

	// マテリアルがあれば、マテリアル属性を取得
	if (name.C_Str() != "DefaultMaterial")
	{
		aiColor3D ambient = { 0.0f, 0.0f, 0.0f };
		aiColor3D diffuse = { 0.0f, 0.0f, 0.0f };
		aiColor3D specular = { 0.0f, 0.0f, 0.0f };

		mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	
		this->mAmbient = D3DXVECTOR3(ambient.r, ambient.g, ambient.b);
		this->mDiffuse = D3DXVECTOR3(diffuse.r, diffuse.g, diffuse.b);
		this->mSpecular = D3DXVECTOR3(specular.r, specular.g, specular.b);
	}
	else
	{
		this->mAmbient = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->mDiffuse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->mSpecular = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// Debugウインドへ
		cout << "<Warning> no material" << endl;
	}

	// ディフューズテクスチャを読み込み
	addTextureFromResources(mat, aiTextureType_DIFFUSE);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Material::~Material()
{

}

//*****************************************************************************
//
// マテリアルによってテクスチャを読み込み
//
//*****************************************************************************
void Material::addTextureFromResources(aiMaterial* mat, aiTextureType type)
{
	for (unsigned int count = 0; count < mat->GetTextureCount(type); count++)
	{
		Resources* resource = getResources();

		// テクスチャパスを読み込み
		aiString path;
		mat->getTexture(type, count, &path);

		// aiStringの文字コードはstringのutf-8
		// ここはwstringのunicodeが欲しい
		wstring wPath = stringUTF8ToUnicode(path.C_Str());

		// テクスチャを読み込み
		resource->createTexture(wPath);

		// 絶対パスならば、モデルの名前とテクスチャを取得
		wstring fileName;
		if (wPath.find(L'\\') != string::npos)
		{
			fileName = wPath.substr(wPath.find_last_of(L'\\') + 1, wPath.find_last_of(L'.'));	// exp: c:\aaa\bbb\ccc.png -> ccc.png
		}
		fileName = fileName.substr(0, fileName.find_first_of(L'.'));							// exp: xxx.png -> xxx

		// テクスチャまだ読み込まなっかたら読み込む
		Texture* texture = resource->getTexture(fileName);
			
		// テクスチャを保存
		this->mTextures.push_back(texture);
	}
}