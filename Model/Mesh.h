//*****************************************************************************
//
// メッシュ処理 [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "..\Engine\Engine.h"
#include "..\Engine\Shader.h"

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
	LPDIRECT3DDEVICE9				mD3DDevice;	// D3Dデバイス

	//-----------Assimp-----------//
	void SetupMesh();

public:
	int							m_polygonNum;	// ポリゴン数
	int							m_vertexNum;	// 頂点数
	DX_VERTEX_3D*				m_vertex;		// 頂点配列
	int							m_IndexNum;		// 頂点インデックス数
	int*						m_Index;		// 頂点インデック配列,[0,1,2][0,2,3]...
	
	Mesh();
	~Mesh();

	void DrawDXMesh();			// メッシュを描画
	HRESULT MakeBuffer();		// 描画用各バッファを作る


	//-----------Assimp-----------//
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures);

	// メッシュデータ
	vector<Vertex>				mVertices;
	vector<unsigned int>		mIndices;
	vector<Texture>				mTextures;

	void Draw(Shader *shader);	// ドロー
};



#endif // !_MESH_H_
