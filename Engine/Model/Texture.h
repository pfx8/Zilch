//*****************************************************************************
//
// テクスチャ処理 [Texture.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../Engine.h"

enum TextureType
{
	TT_diffuse,
	TT_effect,
};

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Texture
{
private:
	LPDIRECT3DTEXTURE9			mTex;		// テクスチャポインタ
	TextureType					mType;		// テクスチャタイプ
	string						mPath;		// テクスチャパス
	LPDIRECT3DDEVICE9			mD3DDevice;		// D3Dデバイス

public:
	Texture(string path, TextureType type);
	~Texture();

	HRESULT loadingTexture();		// テクスチャを読み込み
};

#endif // !_TEXTURE_H_

