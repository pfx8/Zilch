//*****************************************************************************
//
// 座標変換済み頂点で2D板ポリゴンを描画 [ScreenPolygon.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCREEN_POLYGON_H_
#define _SCREEN_POLYGON_H_

#include "Character.h"
#include "..\Engine.h"
#include "..\ResourcesManager.h"
#include "..\Shader\RHWShader.h"

#define MINIMAP_SIZE (SCREEN_HEIGHT / 3)

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class ScreenPolygon
{
private:
	RHWShader*	RHWshader;	// 変換済み用シェーダー

	void DrawObject(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DTEXTURE9 titleTexture, int level = 9, float alpha = 0.0f, bool needa = false);	// 動的なものを描画する
	void MakeVertexDecl();																				// 頂点宣言
	HRESULT MakeVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint);	// 頂点作成
	HRESULT MakeTransVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint, float rot);	// 頂点作成
	HRESULT MakeIndex();																				// インデックス作成

public:
	ResourcesManager*				resourcesManager;		// リソースマネジメント

	IDirect3DVertexDeclaration9*	vertexDecl;				// 頂点シェーダー宣言
	LPDIRECT3DINDEXBUFFER9			indexBuffer;			// 頂点インデックスバッファ(共有)

	LPDIRECT3DVERTEXBUFFER9			UIminiMapVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIminiMapTexture;		// フィールドテクスチャ

	LPDIRECT3DVERTEXBUFFER9			UIminiMapPlayerVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIminiMapPlayerTexture;			// フィールドテクスチャ

	LPDIRECT3DVERTEXBUFFER9			UIminiMapEnemyVertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIminiMapEnemyTexture;			// フィールドテクスチャ

	LPDIRECT3DVERTEXBUFFER9			UIHPVertexBuffer[3];	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIHPTexture;			// フィールドテクスチャ
	int								HP;

	LPDIRECT3DVERTEXBUFFER9			UIpanVertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIpanTexture;			// フィールドテクスチャ
	D3DXMATRIX						pan;					// 回転行列

	LPDIRECT3DVERTEXBUFFER9			UIzenVertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIzenTexture;			// フィールドテクスチャ

	LPDIRECT3DVERTEXBUFFER9			UIstopVertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIstopTexture;			// フィールドテクスチャ

	LPDIRECT3DVERTEXBUFFER9			UIgouVertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIgouTexture;			// フィールドテクスチャ
	LEVER_LEVEL						level;					// 船の状態

	LPDIRECT3DVERTEXBUFFER9			UIleftVertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIleftTexture;			// フィールドテクスチャ

	LPDIRECT3DVERTEXBUFFER9			UIrightVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9				UIrightTexture;			// フィールドテクスチャ
	float							leftShooting;
	float							rightShooting;

	ScreenPolygon();
	~ScreenPolygon();

	void Draw();
	void Update(Character* player, Character* enemy);
};


#endif // !_SCREEN_POLYGON_H_