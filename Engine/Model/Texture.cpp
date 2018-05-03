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
Texture::Texture(string name, string path)
{
	this->mTex = nullptr;

	// テクスチャの名前を取得
	this->mName = name;
	
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
HRESULT Texture::loadingTexture(string path)
{
	LPDIRECT3DDEVICE9	D3dDevice = getD3DDevice();

	// テクスチャを読み込み
	if (FAILED(D3DXCreateTextureFromFile(
		D3dDevice,
		path.data(),
		&mTex)))
	{
		cout << "[Error] Loading <Texture> " << path << " ... fail!" << endl;	// コンソールにメッセージを出す
		return E_FAIL;
	}

	return S_OK;
}