//*****************************************************************************
//
// メッシュ処理 [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "Texture.h"
#include "../Engine.h"
#include "../Shader.h"

struct Vertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;

	// プラスインフォメーション
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 bitangent;
};

class Mesh
{
private:
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;	// 頂点インデックスバッファ
	IDirect3DVertexDeclaration9*	mVertexDecl;	// 頂点シェーダー宣言

	HRESULT SetupMesh();							// メッシュをセットアップ

public:
	// メッシュデータ
	vector<Vertex>					mVertices;
	vector<unsigned int>			mIndices;
	vector<Texture>					mTextures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures);
	~Mesh();

	void draw(Shader *shader);	// ドロー
};



#endif // !_MESH_H_
