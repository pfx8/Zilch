//*****************************************************************************
//
// テクスチャ処理 [Texture.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "..\Engine.h"

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
	wstring						mName;			// テクスチャ名前
	LPDIRECT3DTEXTURE9			mTex;			// テクスチャポインタ

	Texture(wstring name, wstring path);
	~Texture();

	HRESULT loadingTexture(wstring path);		// テクスチャを読み込み
};

#endif // !_TEXTURE_H_

