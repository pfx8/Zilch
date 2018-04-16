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
Mesh::Mesh(MeshType type, aiMesh* mesh, const aiScene* scene)
{
	// メッシュタイプを設定
	this->mMeshType = type;
	// バッファポインタを初期化
	this->mVertexBuffer = nullptr;
	this->mIndexBuffer = nullptr;

	// 頂点フォーマット宣言ポイントを初期化
	this->mVertexDecl = nullptr;

	// メッシュを読み込み&メッシュのバッファを作り
	switch (this->mMeshType)
	{
	case MT_default:
		createMesh(mesh, scene);
		SetupMesh();
		break;
	case MT_withBone:
		createMeshWithBone(mesh, scene);
		SetupMeshWithBone();
		break;
	}

}

//*****************************************************************************
//
// 骨付きメッシュを読み込み
//
//*****************************************************************************
void Mesh::createMeshWithBone(aiMesh *mesh, const aiScene *scene)
{
	cout << "   <Mesh Name> : [" << mesh->mName.C_Str() << "]" << endl;

	unsigned int	numBones = 0;		// 骨の数
	unordered_map<string, Bone>		boneMapping;		//	骨マップ

	// 頂点処理
	for (unsigned int count = 0; count < mesh->mNumVertices; count++)
	{
		VertexBone vertex;

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

	// 骨処理
	for (unsigned int count = 0; count < mesh->mNumBones; count++)
	{
		unsigned int boneIndex = 0;
		string boneName{ mesh->mBones[count]->mName.C_Str() };			// 骨の名前を取得

		cout << "      <Bone Name> [" << count << "] " << boneName << endl;

		// 新しい骨ならば
		if (boneMapping.find(boneName) == boneMapping.end())
		{
			// 骨の番号を付き
			boneIndex = numBones;
			numBones++;

			// 骨データを保存
			D3DXMATRIX offset(mesh->mBones[count]->mOffsetMatrix[0]);		// aiMatrixからD3DXMATRIXへ変更
			Bone bone = Bone(boneIndex, offset);
			boneMapping[boneName] = bone;
		}
		else
		{
			// 骨マップから骨の番後を取得
			boneIndex = boneMapping[boneName].mIndex;
		}

		// 頂点に骨情報を入れる
		for (unsigned int i = 0; i < mesh->mBones[count]->mNumWeights; i++)
		{
			// 今の骨に対して各影響されてる頂点のIDと重みを取得
			unsigned int vertexID = mesh->mBones[count]->mWeights[i].mVertexId;
			float weight = mesh->mBones[count]->mWeights[i].mWeight;

			// 頂点に情報を入れる
			for (unsigned int j = 0; j < NUM_BONES_PER_VEREX; j++)
			{
				if (mVertices.at(vertexID).weights[j] == 0)
				{
					mVertices.at(vertexID).boneID[j] = boneIndex;
					mVertices.at(vertexID).weights[j] = weight;
				}
			}
		}
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
// デフォルトメッシュを読み込み
//
//*****************************************************************************
void Mesh::createMesh(aiMesh *mesh, const aiScene *scene)
{
	cout << "   <Mesh Name> : [" << mesh->mName.C_Str() << "]" << endl;

	unsigned int	numBones = 0;		// 骨の数
	unordered_map<string, Bone>		boneMapping;		//	骨マップ

	// 頂点処理
	for (unsigned int count = 0; count < mesh->mNumVertices; count++)
	{
		VertexBone vertex;

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

		for (unsigned int i = 0; i < face.mNumIndices; i = i + 3)
		{
			// フェースによって各頂点のインデックスを取得
			// DXのポリゴン描きルールは反時計回りなので、ここで変更
			this->mIndices.push_back(face.mIndices[i]);
			this->mIndices.push_back(face.mIndices[i + 2]);
			this->mIndices.push_back(face.mIndices[i + 1]);
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
HRESULT Mesh::SetupMeshWithBone()
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
	if (FAILED(pD3DDevice->CreateVertexBuffer(mVertices.size() * sizeof(VertexBone), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &this->mVertexBuffer, NULL)))
	{
		cout << "[Error] <Mesh> Make vertex buffer ... fail!" << endl;	// エラーメッセージ
		return E_FAIL;
	}
		
	VertexBone* vertices = nullptr;
		
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
// デフォルトメッシュをセットアップ
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
	shader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);

	// カメラの行列をシェーダーに渡る
	shader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	shader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);

	// テクスチャを渡す
	LPDIRECT3DTEXTURE9	 diffuse = this->mMaterials.at(0)->mTextures.at(0)->mTex;
	shader->mEffect->SetTexture("diffuse", diffuse);

	// 描画
	UINT passNum = 0;
	shader->mEffect->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		// 各パスを描画
		shader->mEffect->BeginPass(count);

		HRESULT hr;
		hr = pD3DDevice->SetVertexDeclaration(this->mVertexDecl);													// 頂点宣言を設定
		switch (this->mMeshType)																												// 頂点バッファを設定
		{	
		case MT_default:
			hr = pD3DDevice->SetStreamSource(0, this->mVertexBuffer, 0, sizeof(Vertex));
			break;
		case MT_withBone:
			hr = pD3DDevice->SetStreamSource(0, this->mVertexBuffer, 0, sizeof(VertexBone));	
			break;
		}
		hr = pD3DDevice->SetIndices(this->mIndexBuffer);																	// インデックスバッファを設定
		unsigned int vertexNums = mVertices.size();
		unsigned int faceNums = mIndices.size() / 3;
		hr = pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNums, 0, faceNums);	// ポリゴンの描画

		shader->mEffect->EndPass();
	}
	shader->mEffect->End();
}