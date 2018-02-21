//*****************************************************************************
//
// 平面処理[Plane.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _PLANE_H_
#define _PLANE_H_

#include "Shader.h"
#include "../Engine.h"

struct PLANEVERTEX
{
	D3DXVECTOR4 position;		// 頂点座標
	D3DXVECTOR2 texture;		// テクスチャ座標
};

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Plane
{
private:
	void SetWorldMatrix();	// ワールド変換
	virtual HRESULT MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// 頂点宣言

public:
	D3DXMATRIX		worldMatrix;	// ワールド変換マトリックス
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR2		planeSize;
	D3DXVECTOR2		planeNum;

	int				vertexNum;		// 頂点数
	int				polygonNum;		// ポリゴン数
	int				indexNum;		// インデックス数

	IDirect3DVertexDeclaration9*	vertexDecl;		// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			indexBuffer;	// 頂点インデックスバッファ
	LPDIRECT3DTEXTURE9				tex;			// フィールドテクスチャ

	Plane();
	~Plane();

	virtual HRESULT InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// 座標を設定
	virtual void Draw(Shader* shader, D3DXMATRIX* vMatrix, D3DXMATRIX* pMatrix);				// テクスチャを描画する(PixelShader)

	void Update();
};
#endif // !_PLANE_H_
