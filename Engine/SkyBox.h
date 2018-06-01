//*****************************************************************************
//
// スカイボックス処理 [SkyBox.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "Engine.h"
#include "Shader.h"

//*****************************************************************************
//
// 頂点設計
//
//*****************************************************************************
typedef struct SKYBOXVERTEX
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR2 uv;		// UV座標
}SKYBOXVERTEX;

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SkyBox
{
private:
	D3DXVECTOR3						pos;			// 座標
	IDirect3DVertexDeclaration9*	vertexDecl;		// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9			indexBuffer;	// インデックスバッファ
	float							length;		// ボックスの長さ

public:
	D3DXMATRIX						wMatrix;	// ワールド変換マトリックス
	LPDIRECT3DTEXTURE9				tex;		// テクスチャ配列
	
	SkyBox(void);
	~SkyBox(void);

	HRESULT InitSkyBox(float length);		// スカイボックスを初期化
	void SetWorldMatrix(void);					// ワールド変換
	void draw(Shader* mShader, D3DXMATRIX* vMatrix, D3DXMATRIX* pMatrix);	// スカイボックスを描画
};

#endif // !_SKY_BOX_H_