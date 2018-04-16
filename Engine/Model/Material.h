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
#include "../Resources.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Material
{
private:
	string								name;					// マテリアルの名前

public:
	vector<Texture*>			textures;				// テクスチャ
	D3DXVECTOR3				ambient;				// 環境光
	D3DXVECTOR3				diffuse;				// 拡散反射光
	D3DXVECTOR3				specular;				// 鏡面反射光
	float								shininess;			// 光沢

	// マテリアルがなければデフォルトで初期化
	Material(aiMaterial* mat);
	~Material();

	// マテリアルを読み込み
	void loadingMaterial(aiMaterial* mat);

	// マテリアルによってテクスチャを読み込み
	void addTextureFromResources(aiMaterial* mat, aiTextureType mType);
};

#endif // !_MATERIAL_H
