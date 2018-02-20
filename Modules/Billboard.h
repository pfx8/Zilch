//*****************************************************************************
//
// ビルボード処理 [billboard.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BILLBOARD_H_
#define  _BILLBOARD_H_

#include "../Engine.h"
#include "Character.h"

#define	BILLBOARD_SIZE_X		(10.0f)							// ビルボードの幅
#define	BILLBOARD_SIZE_Y		(10.0f)							// ビルボードの高さ

typedef struct BILLBOARDVERTEX
{
	D3DXVECTOR3 position;		// 頂点座標
	D3DXVECTOR3 normal;			// 法線
	D3DCOLOR	diffuse;		// 反射光
	D3DXVECTOR2 tex;			// テクスチャ座標
}BILLBOARDVERTEX;

#define	FVF_BILLBOARDVERTEX	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class BillBoard
{
private:
	HRESULT MakeVertexBillboard();	// 頂点作成

public:
	LPDIRECT3DTEXTURE9		titleTexture;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;				// 頂点バッファ

	D3DXMATRIX				worldMatrix;				// ワールドマトリックス
	D3DXVECTOR3				pos;						// 位置
	D3DXVECTOR3				scl;						// スケール

	D3DXVECTOR3				moveSpeedVec;				// 移動量
	D3DXVECTOR3				accelerarion;				// 水平加速度

	bool					isUse;

	BillBoard();
	~BillBoard();

	void Init();
	void Update();
	void Draw(D3DXMATRIX viewMatrix);
	void SetVertexBillboardByship(float sizeX, float sizeY, Character* ship, bool isLeft);	// 頂点座標を設定
};
#endif // !_BILLBOARD_H_






