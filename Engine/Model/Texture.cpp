﻿//*****************************************************************************
//
// テクスチャ処理 [Texture.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Texture.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Texture::Texture(wstring path)
{
	// テククシャポインタを初期化
	this->mTex = nullptr;

	// テクスチャ情報取得
	this->mName = pathToFileName(path);
	this->mPath = path;
	
	// テクスチャを読み込み
	loadingTexture(path);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Texture::~Texture()
{

}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT Texture::loadingTexture(wstring path)
{
	LPDIRECT3DDEVICE9 D3dDevice = getD3DDevice();

	// テクスチャを読み込み
	if (FAILED(D3DXCreateTextureFromFile(
		D3dDevice,
		path.data(),
		&mTex)))
	{
		// Debugウインドへ
		wcout << "<Error> loading<Texture> " << path << " ... failed!" << endl;
		return E_FAIL;
	}

	// Debugウインドへ
	wcout << "<Scene> loading<Texture> " << path  << " ... sucessed!"<< endl;

	return S_OK;
}