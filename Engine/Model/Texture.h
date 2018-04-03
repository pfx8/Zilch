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

private:
	LPDIRECT3DTEXTURE9			mTex;		// テクスチャポインタ
	string						mPath;		// テクスチャパス

public:
	Texture(string path);
	~Texture();

	HRESULT loadingTexture();		// テクスチャを読み込み

	string getTexPath()
	{
		return this->mPath;
	}

	void deleteTex()
	{
		RELEASE_POINT(mTex);
	}
};

#endif // !_TEXTURE_H_

