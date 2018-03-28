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

class DX_MESH
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;	// 頂点インデックスバッファ
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DDEVICE9				m_D3DDevice;		// D3Dデバイス

public:
	int							m_polygonNum;	// ポリゴン数
	int							m_vertexNum;	// 頂点数
	DX_VERTEX_3D*				m_vertex;		// 頂点配列
	int							m_IndexNum;		// 頂点インデックス数
	int*						m_Index;		// 頂点インデック配列,[0,1,2][0,2,3]...

	DX_MESH();
	~DX_MESH();

	void DrawDXMesh();		// メッシュを描画
	HRESULT MakeBuffer();		// 描画用各バッファを作る
};



#endif // !_MESH_H_
