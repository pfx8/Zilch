//*****************************************************************************
//
// テクスチャ処理 [Texture.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Engine/Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Texture
{
	friend class Model;
	friend class Material;

private:

public:
	string						mName;		// テクスチャ名前
	LPDIRECT3DTEXTURE9			mTex;		// テクスチャポインタ

	Texture(string name, string path);
	~Texture();

	HRESULT loadingTexture(string path);	// テクスチャを読み込み
};

#endif // !_TEXTURE_H_

