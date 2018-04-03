//*****************************************************************************
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
Texture::Texture(string path)
{
	this->mFileName = path;
	this->mTex = nullptr;

	// テクスチャを読み込み
	loadingTexture();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Texture::~Texture()
{
	RELEASE_POINT(mTex);
}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT Texture::loadingTexture()
{
	LPDIRECT3DDEVICE9	D3dDevice = GetDevice();

	// テクスチャを読み込み
	if (FAILED(D3DXCreateTextureFromFile(
		D3dDevice,
		mFileName.data(),
		&mTex)))
	{
		cout << "[Error] Loading <Texture> " << mFileName << " ... Fail!" << endl;	// コンソールにメッセージを出す
		return E_FAIL;
	}

	cout << "[Information] Loading <Texture> " << mFileName << " ... Success!" << endl;	// コンソールにメッセージを出す

	return S_OK;
}