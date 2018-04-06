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

//--------------Assimp--------------//
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Material
{
	friend class Model;
private:
	vector<Texture*>		mTexturesLoaded;				// テクスチャ
	string							mName;								// マテリアルの名前

public:
	D3DXVECTOR3			mAmbient;				// 環境光
	D3DXVECTOR3			mDiffuse;				// 拡散反射光
	D3DXVECTOR3			mSpecular;				// 鏡面反射光

	float							mShininess;			// 光沢

	// マテリアルがなければデフォルトで初期化
	Material(aiMaterial* mat);
	~Material();

	// マテリアルを読み込み
	void loadingMaterial(aiMaterial* mat);

	// マテリアルによってテクスチャを読み込み
	vector<Texture*> loadMaterialTexture(aiMaterial* mat, aiTextureType mType, string typeName);
};

#endif // !_MATERIAL_H
