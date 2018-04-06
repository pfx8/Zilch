//*****************************************************************************
//
// マテリアル処理 [Material.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Texture.h"
#include "../Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Material
{
	friend class Model;
private:
	vector<Texture>		mTextures;				// テクスチャ
	string							mName;					// マテリアルの名前

public:
	D3DXVECTOR3			mAmbient;				// 環境光
	D3DXVECTOR3			mDiffuse;				// 拡散反射光
	D3DXVECTOR3			mSpecular;				// 鏡面反射光

	float							mShininess;			// 光沢

	Material(string name, D3DXVECTOR3 ambient, D3DXVECTOR3 diffuse, D3DXVECTOR3 specular);
	~Material();
};

#endif // !_MATERIAL_H
