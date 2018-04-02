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
Texture::Texture(string path, TextureType type)
{
	this->mD3DDevice = GetDevice();

	this->mPath = path;
	this->mType = type;
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
	RELEASE_POINT(mD3DDevice);
	RELEASE_POINT(mTex);
}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT Texture::loadingTexture()
{
	// テクスチャを読み込み
	if (FAILED(D3DXCreateTextureFromFile(
		mD3DDevice,
		mPath.c_str(),
		&mTex)))
	{
		cout << "[Error] Loading <Texture> " << mPath << " ... Fail!" << endl;	// コンソールにメッセージを出す
		return E_FAIL;
	}

	cout << "[Information] Loading <Texture> " << mPath << " ... Success!" << endl;	// コンソールにメッセージを出す

	return S_OK;
}