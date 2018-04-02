//*****************************************************************************
//
// メッシュ処理 [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "..\Engine.h"
#include "..\Shader.h"

struct Vertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;

	// プラスインフォメーション
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 bitangent;
};

struct Texture
{
	LPDIRECT3DTEXTURE9 point;
	string type;
	string path;
};

class Mesh
{
private:
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;	// 頂点インデックスバッファ
	IDirect3DVertexDeclaration9*	mVertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DDEVICE9				mD3DDevice;		// D3Dデバイス

	void SetupMesh();

public:
	// メッシュデータ
	vector<Vertex>					mVertices;
	vector<unsigned int>			mIndices;
	vector<Texture>					mTextures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures);
	~Mesh();

	HRESULT MakeBuffer();		// 描画用各バッファを作る
	void Draw(Shader *shader);	// ドロー
};



#endif // !_MESH_H_
