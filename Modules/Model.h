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


//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Model
{
private:
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR3		rot;			// 回転
	D3DXVECTOR3		scl;			// 拡大縮小
	D3DXVECTOR3		upVector;		// カメラの上方向ベクトル
	D3DXVECTOR3		lookVector;		// カメラの注視方向ベクトル
	D3DXVECTOR3		rightVector;	// カメラの右方向ベクトル
	D3DXMATRIX		worldMatrix;	// ワールド変換マトリックス

	void SetWorldMatrix();						// ワールド変換
	void RotationVecUp(float angle);			// 上方向のベクトルにして回転

public:
	LPD3DXMESH						meshPoint;			// メッシュ情報へのポインタ
	LPDIRECT3DTEXTURE9				meshTexturePoint;	// テクスチャマネジメント
	Material*						material;			// マテリアル情報へのポインタ
	IDirect3DVertexDeclaration9*	vertexDecl;			// 頂点宣言

	Model();
	~Model();

	void Update();	// 更新
	void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);	// モデルを描画する
};

#endif // !_MODEL_H_

