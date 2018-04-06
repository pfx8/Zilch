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
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture*>  textures)
{
	LPDIRECT3DDEVICE9	D3dDevice = GetDevice();

	// メッシュデータコンテナを初期化
	mVertices = vertices;
	mIndices = indices;
	mTextures = textures;

	// バッファポインタを初期化
	mVertexBuffer = nullptr;
	mIndexBuffer = nullptr;

	// 頂点フォーマット宣言ポイントを初期化
	mVertexDecl = nullptr;

	// メッシュのバッファを作り
	SetupMesh();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Mesh::~Mesh()
{
	RELEASE_POINT(mVertexBuffer);
	RELEASE_POINT(mIndexBuffer);
}

//*****************************************************************************
//
// メッシュを設定
//
//*****************************************************************************
HRESULT Mesh::SetupMesh()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 Decl[] =		// 頂点データのレイアウトを定義
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
			{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(Decl, &mVertexDecl);
	}

	// 頂点バッファ作成
	if (FAILED(pDevice->CreateVertexBuffer(mVertices.size() * sizeof(Vertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &mVertexBuffer, NULL)))
	{
		cout << "[Error] <Mesh> Make vertex buffer ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}
		
	Vertex* vertices = nullptr;
		
	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得
	mVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	unsigned int count = 0;
	for (auto it : mVertices)
	{
		vertices[count].pos = it.pos;
		vertices[count].nor = it.nor;
		vertices[count].tex = it.tex;
		vertices[count].tangent = it.tangent;
		vertices[count].bitangent = it.bitangent;

		// test
		//cout << "-> (" << vertices[count].pos.x << ", " << vertices[count].pos.y << ", " << vertices[count].pos.z << ")" << endl;

		count++;
	}

	// 頂点データをアンロック
	mVertexBuffer->Unlock();

	// 頂点インデックスバッファ作成
	if (FAILED(pDevice->CreateIndexBuffer(mIndices.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mIndexBuffer, NULL)))
	{
		cout << "[Error] <Mesh> Make index buffer ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}

	unsigned int* vertexIndex = nullptr;

	// インデックス データのある一定範囲をロックし、そのインデックスバッファメモリーへのポインターを取得
	mIndexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);

	count = 0;
	for (auto it : mIndices)
	{
		vertexIndex[count] = it;
	}

	// インデックス データのロックを解除
	mIndexBuffer->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// メッシュをドロー
//
//*****************************************************************************
void Mesh::draw(Shader *shader)
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