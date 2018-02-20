//*****************************************************************************
//
// モデル処理 [Model.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

#include "Material.h"
#include "..\Engine.h"
#include "..\Shader\CelShader.h"

enum Model_Type
{
	MT_ship = 0,
	MT_bullet,
};

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Model
{
private:

public:
	LPD3DXMESH						meshPoint;			// メッシュ情報へのポインタ
	LPDIRECT3DTEXTURE9				meshTexturePoint;	// テクスチャマネジメント
	Material*						material;			// マテリアル情報へのポインタ
	IDirect3DVertexDeclaration9*	vertexDecl;			// 頂点宣言

	Model();
	~Model();

	void DrawModel(CelShader* celShader, D3DXMATRIX* worldMatrix, D3DXMATRIX* VPMatrix,
		D3DXMATRIX* lightMatrix, D3DXMATRIX* normalMatrix, Model_Type modelType);	// モデルを描画する
};

#endif // !_MODEL_H_

