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
Mesh::Mesh(aiMesh* mesh, const aiScene* scene)
{
	// バッファポインタを初期化
	mVertexBuffer = nullptr;
	mIndexBuffer = nullptr;

	// 頂点フォーマット宣言ポイントを初期化
	mVertexDecl = nullptr;

	// メッシュを読み込み
	loadingMesh(mesh, scene);
	// メッシュのバッファを作り
	SetupMesh();
}

//*****************************************************************************
//
// メッシュを読み込み
//
//*****************************************************************************
void Mesh::loadingMesh(aiMesh *mesh, const aiScene *scene)
{
	cout << "   <Mesh Name> : [" << mesh->name.C_Str() << "]" << endl;

	// 頂点処理
	for (unsigned int count = 0; count < mesh->mNumVertices; count++)
	{
		Vertex vertex;

		// 位置
		// blender座標とDX座標が違うので、Y軸とZ軸を交換
		vertex.pos.x = mesh->mVertices[count].x;
		vertex.pos.y = -mesh->mVertices[count].z;
		vertex.pos.z = -mesh->mVertices[count].y; 
		//vertex.pos.x = mesh->mVertices[count].x;
		//vertex.pos.y = mesh->mVertices[count].y;
		//vertex.pos.z = mesh->mVertices[count].z;

		// 法線
		vertex.nor.x = mesh->mNormals[count].x;
		vertex.nor.y = mesh->mNormals[count].y;
		vertex.nor.z = mesh->mNormals[count].z;

		// UV座標
		if (mesh->mTextureCoords[0])	// テクスチャ0から(Maxは8で)
		{
			vertex.tex.x = mesh->mTextureCoords[0][count].x;
			vertex.tex.y = mesh->mTextureCoords[0][count].y;
			
			//cout << "<Test><Texture> : " << "X " << vertex.tex.x << ", Y " << vertex.tex.y << endl;
		}
		else
		{
			vertex.tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		// 接線(Tangents)
		/*if (mesh->mTangents)
		{
		vertex.tangent.x = mesh->mTangents[count].x;
		vertex.tangent.y = mesh->mTangents[count].y;
		vertex.tangent.z = mesh->mTangents[count].z;
		}
		else
		{
		vertex.tangent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}*/

		// 従接線(Bitangents)
		/*if (mesh->mBitangents)
		{
		vertex.bitangent.x = mesh->mBitangents[count].x;
		vertex.bitangent.y = mesh->mBitangents[count].y;
		vertex.bitangent.z = mesh->mBitangents[count].z;
		}
		else
		{
		vertex.bitangent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}*/

		// 取得した頂点を頂点コンテナの末尾に追加
		this->mVertices.push_back(vertex);
	}

	// インデックス処理
	for (unsigned int count = 0; count < mesh->mNumFaces; count++)
	{
		aiFace face = mesh->mFaces[count];

		for (unsigned int i = 0; i < face.mNumIndices; i=i+3)
		{
			// フェースによって各頂点のインデックスを取得
			// DXのポリゴン描きルールは反時計回りなので、ここで変更
			this->mIndices.push_back(face.mIndices[i]);
			this->mIndices.push_back(face.mIndices[i+2]);
			this->mIndices.push_back(face.mIndices[i+1]);
		}
	}

	// マテリアル処理
	{
		// フェースのマテリアルを取得
		aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
		Material* mat = new Material(aiMat);
		// メッシュのマテリアルに入れる
		this->mMaterials.push_back(mat);
	}
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
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 Decl[] =		// 頂点データのレイアウトを定義
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		pD3DDevice->CreateVertexDeclaration(Decl, &this->mVertexDecl);
	}

	// 頂点バッファ作成
	if (FAILED(pD3DDevice->CreateVertexBuffer(mVertices.size() * sizeof(Vertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &this->mVertexBuffer, NULL)))
	{
		cout << "[Error] <Mesh> Make vertex buffer ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}
		
	Vertex* vertices = nullptr;
		
	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得
	this->mVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	unsigned int count = 0;
	for (auto it : this->mVertices)
	{
		vertices[count].pos = it.pos;

		vertices[count].nor = it.nor;
		vertices[count].tex = it.tex;
		//vertices[count].tangent = it.tangent;
		//vertices[count].bitangent = it.bitangent;

		//cout << "<Test><Vertex> : [pos" << count <<"] " << it.pos.x << " " << it.pos.y << " " << it.pos.z << endl;

		count++;
	}

	// 頂点データをアンロック
	this->mVertexBuffer->Unlock();

	// 頂点インデックスバッファ作成
	if (FAILED(pD3DDevice->CreateIndexBuffer(this->mIndices.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->mIndexBuffer, NULL)))
	{
		cout << "[Error] <Mesh> Make index buffer ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}

	WORD* vertexIndex = NULL;

	// インデックス データのある一定範囲をロックし、そのインデックスバッファメモリーへのポインターを取得
	this->mIndexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);

	count = 0;
	for (auto it : this->mIndices)
	{
		vertexIndex[count] = it;

		//cout << "<Test><Index> : " << it << endl;
	
		count++;
	}

	// インデックス データのロックを解除
	this->mIndexBuffer->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// メッシュをドロー
//
//*****************************************************************************
void Mesh::draw(Transform* trans, Camera* camera)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();
	Resources* resource = getResources();
	Shader* shader = resource->getShader("phongShading");

	// テクニックを設定
	shader->mEffect->SetTechnique("defaultRender");

	// モデルのワールド変換行列をシェーダーに渡る
	shader->mEffect->SetMatrix("worldMatrix", &trans->worldMatrix);

	// カメラの行列をシェーダーに渡る
	shader->mEffect->SetMatrix("viewMatrix", &camera->viewMatrix);
	shader->mEffect->SetMatrix("projectionMatrix", &camera->projectionMatrix);

	// テクスチャを渡す
	LPDIRECT3DTEXTURE9	 diffuse = this->mMaterials.at(0)->textures.at(0)->mTex;
	shader->mEffect->SetTexture("diffuse", diffuse);

	// 描画
	UINT passNum = 0;
	shader->mEffect->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		// 各パスを描画
		shader->mEffect->BeginPass(count);

		HRESULT hr;
		hr = pD3DDevice->SetVertexDeclaration(this->mVertexDecl);							// 頂点宣言を設定
		hr = pD3DDevice->SetStreamSource(0, this->mVertexBuffer, 0, sizeof(Vertex));				// 頂点バッファを設定
		hr = pD3DDevice->SetIndices(this->mIndexBuffer);											// インデックスバッファを設定
		unsigned int vertexNums = mVertices.size();
		unsigned int faceNums = mIndices.size() / 3;
		hr = pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNums, 0, faceNums);	// ポリゴンの描画

		shader->mEffect->EndPass();
	}
	shader->mEffect->End();
}