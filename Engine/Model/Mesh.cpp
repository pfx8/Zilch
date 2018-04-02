//*****************************************************************************
//
// メッシュ処理 [Mesh.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Mesh.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures)
{
	// D3Dデバイスポインタを取得
	this->mD3DDevice = GetDevice();

	// メッシュデータコンテナを初期化
	this->mVertices = vertices;
	this->mIndices = indices;
	this->mTextures = textures;

	// バッファポインタを初期化
	this->mVertexBuffer = nullptr;
	this->mIndexBuffer = nullptr;
	this->mVertexDecl = nullptr;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Mesh::~Mesh()
{
	RELEASE_POINT(this->mVertexBuffer);
	RELEASE_POINT(this->mIndexBuffer);
	RELEASE_POINT(this->mVertexDecl);
	RELEASE_POINT(this->mD3DDevice);
}

//*****************************************************************************
//
// 描画用各バッファを作る
//
//*****************************************************************************
HRESULT Mesh::MakeBuffer()
{
	//// 頂点シェーダー宣言
	//{
	//	D3DVERTEXELEMENT9 Decl[] =		// 頂点データのレイアウトを定義
	//	{
	//		{ 0,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	//		{ 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
	//		{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
	//		{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	//		D3DDECL_END()
	//	};
	//	mD3DDevice->CreateVertexDeclaration(Decl, &mVertexDecl);
	//}

	//// 頂点バッファ作成
	//{
	//	if (FAILED(mD3DDevice->CreateVertexBuffer(m_vertexNum * sizeof(DX_VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_DX_VERTEX_3D, D3DPOOL_MANAGED, &mVertexBuffer, NULL)))
	//	{
	//		cout << "[Error] Make <Mesh> vertex buffer ... Fail!" << endl;	// エラーメッセージ
	//		return E_FAIL;
	//	}

	//	DX_VERTEX_3D* vertices = NULL;
	//	mVertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	//	for (int count = 0; count < m_vertexNum; count++)
	//	{
	//		vertices[count].position.x = m_vertex[count].position.x;
	//		vertices[count].position.y = m_vertex[count].position.y;
	//		vertices[count].position.z = m_vertex[count].position.z;
	//		vertices[count].position.w = m_vertex[count].position.w;

	//		vertices[count].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	//	}
	//	mVertexBuffer->Unlock();
	//}

	//// 頂点インデックスバッファ作成
	//{
	//	if (FAILED(mD3DDevice->CreateIndexBuffer(m_IndexNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mIndexBuffer, NULL)))
	//	{
	//		cout << "[Error] Make <Mesh> vertex index buffer ... Fail!" << endl;	// エラーメッセージ
	//		return E_FAIL;
	//	}

	//	int* vertexIndex = NULL;		// イデックスの中身を埋める
	//	mIndexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する
	//	int i = 0;
	//	for (int count = 0; count < m_IndexNum; count++)
	//	{
	//		vertexIndex[count] = m_Index[count];
	//		//cout << vertexIndex[count] << ",";
	//		cout << m_Index[count] << ",";
	//		i++;
	//		if (i == 3)
	//		{
	//			i = 0;
	//			cout << endl;
	//		}
	//	}
	//	mIndexBuffer->Unlock();	// インデックス データのロックを解除する
	//}

	return S_OK;
}

//*****************************************************************************
//
// メッシュを設定
//
//*****************************************************************************
void Mesh::SetupMesh()
{

}

//*****************************************************************************
//
// メッシュをドロー
//
//*****************************************************************************
void Mesh::Draw(Shader *shader)
{
	//D3DXMATRIX wMatrix;
	//// ワールドマトリックスを初期化する
	//D3DXMatrixIdentity(&wMatrix);
	//// ワールドマトリクスの初期化
	//mD3DDevice->SetTransform(D3DTS_WORLD, &wMatrix);

	//// 頂点バッファをストリームに入れる
	//mD3DDevice->SetStreamSource(0, mVertexBuffer, 0, sizeof(DX_VERTEX_3D));
	//// 頂点フォーマットを設定
	//mD3DDevice->SetFVF(FVF_DX_VERTEX_3D);
	//// 頂点インデックスを設定
	//mD3DDevice->SetIndices(mIndexBuffer);
	//// 描画
	//mD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexNum, 0, m_IndexNum);


}