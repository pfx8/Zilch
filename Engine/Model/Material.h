//*****************************************************************************
//
// マテリアル処理 [Material.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Mesh.h"
#include "Model.h"
#include "Texture.h"

#include "..\Engine.h"
#include "..\Resources.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Material
{
private:

public:
	wstring				mName;					// マテリアルの名前
	Model*				mParentModel;			// 所属モデルポインタ
	D3DXVECTOR3			mAmbient;				// 環境光
	D3DXVECTOR3			mDiffuse;				// 拡散反射光
	D3DXVECTOR3			mSpecular;				// 鏡面反射光
	float				mShininess;				// 光沢
	vector<Texture*>	mTextures;				// テクスチャ

	// マテリアルがなければデフォルトで初期化
	Material(aiMaterial* mat, Model* model);
	~Material(void);

	// マテリアルを読み込み
	void loadingMaterial(aiMaterial* mat);

	// マテリアルによってテクスチャを読み込み
	void addTextureFromResources(aiMaterial* mat, aiTextureType mType);

	// Assimpから読み込まれたテクスチャパスを絶対パスに変換
	wstring searchTexturePath(wstring texturePathFromAssimp);
};

#endif // !_MATERIAL_H
