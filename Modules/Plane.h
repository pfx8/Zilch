//*****************************************************************************
//
// 平面処理[Plane.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _PLANE_H_
#define _PLANE_H_

#include "../Engine.h"

#define WAVE_SCALE		0.5f // 波の高さ
#define WAVE_STRENGTH	0.5f // 波の強さ
//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Plane
{
private:
	int				scala;

public:
	float			waveAngle;
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
	LPDIRECT3DTEXTURE9				titleTexture;		// フィールドテクスチャ

	Plane();
	~Plane();

	virtual HRESULT MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// 頂点宣言
	virtual HRESULT InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// 座標を設定

	virtual void Draw();				// テクスチャを描画する(PixelShader)
	void SetWorldMatrix();	// 臨時ーーワールド変換
	void Update();
};
#endif // !_PLANE_H_
