//*****************************************************************************
//
// モデル処理 [Model.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Model.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Model::Model()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 数値を初期化
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	this->pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポインタ
	this->meshPoint = NULL;
	this->meshTexturePoint = NULL;

	// クラスポインタ
	this->material = new Material();

	// 頂点宣言
	D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(planeDecl, &this->vertexDecl);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Model::~Model()
{
	// ポインタ
	RELEASE_POINT(this->meshPoint);
	RELEASE_CLASS_POINT(this->meshTexturePoint);

	// クラスポインタ
	RELEASE_CLASS_POINT(this->material);
}

//*****************************************************************************
//
// 上方向のベクトルにして回転
//
//*****************************************************************************
void Model::RotationVecUp(float angle)
{
	// 角度を記録する
	this->rot.y += angle;

	if (this->rot.y >= D3DXToRadian(360.0f))
	{
		this->rot.y = 0.0f;
	}
	if (this->rot.y <= D3DXToRadian(-360.0f))
	{
		this->rot.y = 0.0f;
	}

	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationAxis(&rotMatrix, &this->upVector, angle);					// 回転行列を作る
	D3DXVec3TransformCoord(&this->lookVector, &this->lookVector, &rotMatrix);	// カメラの新しい座標を計算する

	D3DXVec3Normalize(&this->lookVector, &this->lookVector);
	D3DXVec3Cross(&this->rightVector, &this->lookVector, &this->upVector);
	D3DXVec3Normalize(&this->rightVector, &this->rightVector);
	D3DXVec3Cross(&this->upVector, &this->rightVector, &this->lookVector);
	D3DXVec3Normalize(&this->upVector, &this->upVector);

	// OGL -> DX
	this->rightVector = -this->rightVector;
}

//*****************************************************************************
//
// ワールド変換を設定
//
//*****************************************************************************
void Model::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&this->wMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, this->scl.x, this->scl.y, this->scl.z);
	D3DXMatrixMultiply(&this->wMatrix, &this->wMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->rot.y, this->rot.x, this->rot.z);
	D3DXMatrixMultiply(&this->wMatrix, &this->wMatrix, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->wMatrix, &this->wMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// 状態更新
//
//*****************************************************************************
void Model::Update()
{

}

//*****************************************************************************
//
// モデルを描画する(CelShader)
//
//*****************************************************************************
void Model::Draw(Shader* shader2D, D3DXMATRIX* vMatrix, D3DXMATRIX* pMatrix)
{
	// テクニックを設定
	shader2D->effect->SetTechnique("defaultRender");

	// 変更行列を渡す
	shader2D->effect->SetValue("wMat", &this->wMatrix, sizeof(D3DXMATRIX));
	shader2D->effect->SetValue("vMat", vMatrix, sizeof(D3DXMATRIX));
	shader2D->effect->SetValue("pMat", pMatrix, sizeof(D3DXMATRIX));

	// テクスチャを渡す
	shader2D->effect->SetTexture("tex", this->meshTexturePoint);

	unsigned int passNum = 0;
	shader2D->effect->Begin(&passNum, 0);
	for (unsigned count = 0; count < passNum; count++)
	{
		shader2D->effect->BeginPass(count);

		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		DWORD materialNum = this->material->materialNum;				// マテリアル数を取得

		IDirect3DVertexBuffer9* vertexBuffer = NULL;
		this->meshPoint->GetVertexBuffer(&vertexBuffer);				// メッシュ頂点を取得
		IDirect3DIndexBuffer9* indexBuffer = NULL;
		this->meshPoint->GetIndexBuffer(&indexBuffer);					// メッシュ頂点インデックスバッファを取得

		this->meshPoint->GetAttributeTable(NULL, &materialNum);			// メッシュの属性テーブルに格納されているエントリの数を取得

		D3DXATTRIBUTERANGE* attributes = NULL;							// メッシュの属性テーブルを作る
		attributes = new D3DXATTRIBUTERANGE[materialNum];				// エントリ数によって、属性テーブル配列メモリを作り
		this->meshPoint->GetAttributeTable(attributes, &materialNum);	// メッシュの属性テーブルを取得

		pDevice->SetVertexDeclaration(this->vertexDecl);				// 頂点宣言を設定
		pDevice->SetStreamSource(0, vertexBuffer, 0, 32);				// sizeof(POSITION, NORMAL, UV)
		pDevice->SetIndices(indexBuffer);

		// 描画
		for (DWORD count = 0; count < materialNum; count++)
		{
			if (attributes[count].FaceCount)
			{
				//DWORD matNum = attributes[count].AttribId;			// マテリアル数を取得
				//shader->this->effectPoint->SetTexture(shader->this->texture1Handle, this->meshTexturePoint[matNum]);	// テクスチャを設定
				//pDevice->SetTexture(0, this->meshTexturePoint[matNum]);	// テクスチャを設定

				// モデルを描画する
				pDevice->DrawIndexedPrimitive(
					D3DPT_TRIANGLELIST,
					0,
					attributes[count].VertexStart,
					attributes[count].VertexCount,
					attributes[count].FaceStart * 3,
					attributes[count].FaceCount);
			}
		}

		RELEASE_POINT(vertexBuffer);
		RELEASE_POINT(indexBuffer);

		delete[] attributes;

		shader2D->effect->EndPass();
	}
	shader2D->effect->End();
}

//*****************************************************************************
//
// モデルをロードする
//
//*****************************************************************************
HRESULT Model::loadModel(string const &path)
{
	Assimp::Importer import;																// Assimpのインポートを作る
	const aiScene *scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);	// ポリゴンを強制に三角形にする

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "[Error] Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

	// モデルの目録を保存
	this->mModelDirectory = path.substr(0, path.find_last_of('/'));

	// ルートノードから処理を始める
	processNode(scene->mRootNode, scene);
}

//*****************************************************************************
//
// ノード処理
//
//*****************************************************************************
void Model::processNode(aiNode *node, const aiScene *scene)
{
	// もし今のノードにメッシュがあれば処理する
	for (unsigned int count = 0; count < node->mNumMeshes; count++)
	{
		// sceneのmMeshesは本当のメッシュデータ、一歩でnodeのmMesherはメッシュのインデックス
		aiMesh *mesh = scene->mMeshes[node->mMeshes[count]];
		this->mMeshes.push_back(processMesh(mesh, scene));
	}

	// 子供ノードを同じように処理する
	for (unsigned int count = 0; count < node->mNumChildren; count++)
	{
		processNode(node->mChildren[count], scene);
	}
}

//*****************************************************************************
//
// メッシュ処理
//
//*****************************************************************************
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	vector<Vertex> vertices;				// 頂点
	vector<unsigned int> indices;			// 頂点インデックス
	vector<Texture> textures;				// 全部のテクスチャ

	// 頂点処理
	for (unsigned int count = 0; count < mesh->mNumVertices; count++)
	{
		Vertex vertex;

		// 位置
		vertex.pos.x = mesh->mVertices[count].x;
		vertex.pos.y = mesh->mVertices[count].y;
		vertex.pos.z = mesh->mVertices[count].z;

		// 法線
		vertex.nor.x = mesh->mNormals[count].x;
		vertex.nor.y = mesh->mNormals[count].y;
		vertex.nor.z = mesh->mNormals[count].z;

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
		if (mesh->mTangents)
		{
			vertex.tangent.x = mesh->mTangents[count].x;
			vertex.tangent.y = mesh->mTangents[count].y;
			vertex.tangent.z = mesh->mTangents[count].z;
		}
		else
		{
			vertex.tangent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// 従接線(Bitangents)
		if (mesh->mBitangents)
		{
			vertex.bitangent.x = mesh->mBitangents[count].x;
			vertex.bitangent.y = mesh->mBitangents[count].y;
			vertex.bitangent.z = mesh->mBitangents[count].z;
		}
		else
		{
			vertex.bitangent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		// 取得した頂点を頂点コンテナの末尾に追加
		vertices.push_back(vertex);
	}

	// インデックス処理
	for (unsigned int count = 0; count < mesh->mNumFaces; count++)
	{
		aiFace face = mesh->mFaces[count];

		for (unsigned int count = 0; count < face.mNumIndices; count++)
		{
			// フェースによって各頂点のインデックスを取得
			indices.push_back(face.mIndices[count]);
		}
	}
	
	// マテリアル処理
	if (mesh->mMaterialIndex >= 0)
	{
		// フェースのマテリアルを取得
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "diffuseTexture");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());		// 取得したdiffuseMapsをallTextureの後ろに追加
		vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "specularTexture");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());	// 取得したspecularMapsをallTextureの後ろに追加
		vector<Texture> normalMaps = loadMaterialTexture(material, aiTextureType_HEIGHT, "normalTexture");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());		// 取得したnormalMapsをallTextureの後ろに追加
		vector<Texture> heightMaps = loadMaterialTexture(material, aiTextureType_AMBIENT, "heightTexture");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());		// 取得したnormalMapsをallTextureの後ろに追加
	}
	else
	{
		cout << "[Warning] No Material" << endl;
	}

	return Mesh(vertices, indices, textures);
}

//*****************************************************************************
//
// マテリアルからテクスチャを読み込み
//
//*****************************************************************************
vector<Texture> Model::loadMaterialTexture(aiMaterial *mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;	// 読み込んだテクスチャ

	for (unsigned int count = 0; count < mat->GetTextureCount(type); count++)
	{
		aiString str;
		mat->GetTexture(type, count, &str);			// テクスチャパスを読み込み

		bool skip = false;
		for (unsigned int i = 0; i < this->mTexturesLoaded.size(); i++)
		{
			if (strcmp(this->mTexturesLoaded[i].path.data(), str.C_Str()) == 0)
			{
				// テクスチャが読み込まれたかどうかをチェック
				textures.push_back(this->mTexturesLoaded[i]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			// テクスチャまだ読み込まなっかたら読み込む
			Texture mTextures;
			TextureFromFile(str.C_Str(), this->mModelDirectory, mTextures.point);
			mTextures.type = typeName;
			mTextures.path = str.C_Str();
			textures.push_back(mTextures);

			// 読み込んだテクスチャ集合に追加
			this->mTexturesLoaded.push_back(mTextures);
		}
	}

	return textures;
}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT Model::TextureFromFile(const char *path, string const &directory, LPDIRECT3DTEXTURE9 &point)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	string fileName = string(path);
	fileName = directory + '/' + fileName;

	point = nullptr;

	// テクスチャを読み込み
	if (FAILED(D3DXCreateTextureFromFile(
		pDevice,
		fileName.c_str(),
		&point)))
	{
		cout << "[Error] Loading <Texture> " << fileName << " ... Fail!" << endl;	// コンソールにメッセージを出す
		return E_FAIL;
	}
	cout << "[Information] Loading <Texture> " << fileName << " ... Success!" << endl;	// コンソールにメッセージを出す
	return S_OK;
}