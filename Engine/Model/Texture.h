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
// 列挙体
//
//*****************************************************************************
enum TexType
{
	TT_diffuse,
	TT_height,
	TT_specular,
};

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
	TexType						mType;			// テクスチャタイプ
	wstring						mName;			// テクスチャ名前
	wstring						mPath;			// テクスチャパス
	LPDIRECT3DTEXTURE9			mTex;			// テクスチャポインタ

	Texture(wstring path, TexType type);
	~Texture();

	HRESULT loadingTexture(wstring path);		// テクスチャを読み込み
};

#endif // !_TEXTURE_H_

