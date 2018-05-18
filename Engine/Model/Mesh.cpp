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
Mesh::Mesh(aiMesh* mesh, vector<Bone*>& bones, const aiScene* scene, wstring modelPath)
{
	// テクスチャ探すために保存した
	this->mModelPath = modelPath;

	this->mName = stringUTF8ToUnicode(mesh->mName.C_Str());
	this->mMeshInfo.numVertices = mesh->mNumVertices;
	this->mMeshInfo.numFaces = mesh->mNumFaces;
	this->mVertexBuffer = nullptr;
	this->mIndexBuffer = nullptr;
	this->mVertexDecl = nullptr;			// 頂点宣言

	// メッシュを読み込み&メッシュのバッファを作り
	createMesh(mesh, bones, scene);
	setupMesh();
}

//*****************************************************************************
//
// 骨付きメッシュを読み込み
//
//*****************************************************************************
void Mesh::createMesh(aiMesh* mesh, vector<Bone*>& bones, const aiScene *scene)
{
	unsigned int numBones = bones.size();

	// 頂点処理
	for (unsigned int count = 0; count < mesh->mNumVertices; count++)
	{
		VertexDesign vertex;

		// Todo 
		// 軸を判断できる機能

		// blender座標とDX座標が違うので、Y軸とZ軸を交換しなきゃ
		// 位置
		vertex.pos.x = mesh->mVertices[count].x;
		vertex.pos.y = -mesh->mVertices[count].z;
		vertex.pos.z = -mesh->mVertices[count].y; 

		// 法線
		vertex.nor.x = mesh->mNormals[count].x;
		vertex.nor.y = -mesh->mNormals[count].z;
		vertex.nor.z = -mesh->mNormals[count].y;

		// UV座標
		if (mesh->mTextureCoords[0])	// テクスチャ0から(Maxは8で)
		{
			vertex.tex.x = mesh->mTextureCoords[0][count].x;
			vertex.tex.y = mesh->mTextureCoords[0][count].y;
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

		// バウンディングボックスを作り
		createBoundingBox(vertex.pos, this->mBoundingBoxMax, this->mBoundingBoxMin);
	}

	// 骨処理
	for (unsigned int count = 0; count < mesh->mNumBones; count++)
	{
		unsigned int boneIndex =0;

		// 骨の名前を取得
		string boneName = mesh->mBones[count]->mName.C_Str();
		bool skip = false;

		// vector<Bone*>に骨を探す
		for (auto it : bones)
		{
			// もう読み込んだ骨ならば
			if (it->mName == boneName)
			{
				// vector<Bone>から骨の番号を取得
				boneIndex = it->mIndex;
				skip = true;
				break;
			}
		}

		// 新しい骨ならば、vector<Bone*>に増加
		if (skip == false)
		{
			// 骨に番号を付き
			boneIndex = numBones;
			numBones++;
			// 骨データを保存
			D3DXMATRIX offset = mesh->mBones[count]->mOffsetMatrix[0];		// aiMatrixからD3DXMATRIXへ変更
			Bone *bone = new Bone(boneIndex, offset, boneName);
			bones.push_back(bone);
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
				if (mVertices.at(vertexID).weights[j] == 0.0f)
				{
					mVertices.at(vertexID).boneID[j] = boneIndex;
					mVertices.at(vertexID).weights[j] = weight;

					// test data
					mVertices.at(vertexID).boneNum++;

					break;
				}
			}
		}
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
			this->mIndices.push_back(face.mIndices[i+2]);
			this->mIndices.push_back(face.mIndices[i+1]);
		}
	}

	// マテリアル処理
	{
		// フェースのマテリアルを取得
		aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
		Material* mat = new Material(aiMat, this->mModelPath);
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
HRESULT Mesh::setupMesh()
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 Decl[] =		// 頂点データのレイアウトを定義
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
			{ 0, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
			D3DDECL_END()
		};
		pD3DDevice->CreateVertexDeclaration(Decl, &this->mVertexDecl);
	}

	setupVertices();

	setupIndexes();

	return S_OK;
}

//*****************************************************************************
//
// 頂点をセットアップ
//
//*****************************************************************************
HRESULT Mesh::setupVertices()
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// 頂点バッファ作成
	if (FAILED(pD3DDevice->CreateVertexBuffer(mVertices.size() * sizeof(VertexDesign), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &this->mVertexBuffer, NULL)))
	{
		// Debugウインドへ
		cout << "<Error> make vertex buffer ... failed!" << endl;
		return E_FAIL;
	}

	VertexDesign* vertices = nullptr;

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

		count++;
	}

	// 頂点データをアンロック
	this->mVertexBuffer->Unlock();
}

//*****************************************************************************
//
// インデックスをセットアップ
//
//*****************************************************************************
HRESULT Mesh::setupIndexes()
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// 頂点インデックスバッファ作成
	if (FAILED(pD3DDevice->CreateIndexBuffer(this->mIndices.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->mIndexBuffer, NULL)))
	{
		// Debugウインドへ
		cout << "<Error> make index buffer ... failed!" << endl;
		return E_FAIL;
	}

	WORD* vertexIndex = nullptr;

	// インデックス データのある一定範囲をロックし、そのインデックスバッファメモリーへのポインターを取得
	this->mIndexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);

	unsigned int count = 0;
	for (auto it : this->mIndices)
	{
		vertexIndex[count] = it;

		count++;
	}

	// インデックス データのロックを解除
	this->mIndexBuffer->Unlock();
}

//*****************************************************************************
//
// メッシュのシャドウマップを描画
//
//*****************************************************************************
void Mesh::drawShadow(Shader* shader)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// 描画
	UINT passNum = 0;
	shader->mEffect->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		// 各パスを描画
		shader->mEffect->BeginPass(count);

		HRESULT hr;
		// 頂点宣言を設定
		hr = pD3DDevice->SetVertexDeclaration(this->mVertexDecl);
		// 頂点バッファを設定
		hr = pD3DDevice->SetStreamSource(0, this->mVertexBuffer, 0, sizeof(VertexDesign));
		// インデックスバッファを設定
		hr = pD3DDevice->SetIndices(this->mIndexBuffer);

		unsigned int vertexNums = mVertices.size();
		unsigned int faceNums = mIndices.size()/3;
		hr = pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNums, 0, faceNums);	// ポリゴンの描画

		shader->mEffect->EndPass();
	}
	shader->mEffect->End();
}

//*****************************************************************************
//
// メッシュをドロー
//
//*****************************************************************************
void Mesh::drawModel(Shader* shader)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// マテリアル属性を渡す
	shader->mEffect->SetValue("matAmibent", this->mMaterials.at(0)->mAmbient, sizeof(D3DXVECTOR3));
	shader->mEffect->SetValue("matDiffuse", this->mMaterials.at(0)->mDiffuse, sizeof(D3DXVECTOR3));
	shader->mEffect->SetValue("matSpecular", this->mMaterials.at(0)->mSpecular, sizeof(D3DXVECTOR3));
	shader->mEffect->SetFloat("shininess", this->mMaterials.at(0)->mShininess);

	// テクスチャを渡す
	LPDIRECT3DTEXTURE9 tex = this->mMaterials.at(0)->mTextures.at(0)->mTex;
	shader->mEffect->SetTexture("tex", tex);

	// 描画
	UINT passNum = 0;
	shader->mEffect->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		// 各パスを描画
		shader->mEffect->BeginPass(count);

		HRESULT hr;
		// 頂点宣言を設定
		hr = pD3DDevice->SetVertexDeclaration(this->mVertexDecl);
		// 頂点バッファを設定
		hr = pD3DDevice->SetStreamSource(0, this->mVertexBuffer, 0, sizeof(VertexDesign));	
		// インデックスバッファを設定
		hr = pD3DDevice->SetIndices(this->mIndexBuffer);

		unsigned int vertexNums = mVertices.size();
		unsigned int faceNums = mIndices.size()/3;
		hr = pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNums, 0, faceNums);	// ポリゴンの描画

		shader->mEffect->EndPass();
	}
	shader->mEffect->End();
}

//*****************************************************************************
//
// バウンディングボックスサイズを作り
//
//*****************************************************************************
void Mesh::createBoundingBox(D3DXVECTOR3 vertexPos, D3DXVECTOR3 &boxMax, D3DXVECTOR3 &boxMin)
{
	if (vertexPos.x > boxMax.x) boxMax.x = vertexPos.x;
	if (vertexPos.x < boxMin.x) boxMin.x = vertexPos.x;
	if (vertexPos.y > boxMax.y) boxMax.y = vertexPos.y;
	if (vertexPos.y < boxMin.y) boxMin.y = vertexPos.y;
	if (vertexPos.z > boxMax.z) boxMax.z = vertexPos.z;
	if (vertexPos.z < boxMin.z) boxMin.z = vertexPos.z;
}