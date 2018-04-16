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
	string										mPath;		// テクスチャパス

public:
	LPDIRECT3DTEXTURE9			mTex;		// テクスチャポインタ

	Texture(string path);
	~Texture();

	HRESULT loadingTexture();		// テクスチャを読み込み

	string getTexPath()
	{
		return this->mPath;
	}
};

#endif // !_TEXTURE_H_

