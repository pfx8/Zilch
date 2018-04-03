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
	LPDIRECT3DDEVICE9	D3dDevice = GetDevice();

	// 数値を初期化
	upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポインタ
	meshPoint = NULL;
	meshTexturePoint = NULL;

	// クラスポインタ
	material = new Material();

	// 頂点宣言
	D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	D3dDevice->CreateVertexDeclaration(planeDecl, &vertexDecl);
}

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Model::Model(string const &mPath)
{
	LPDIRECT3DDEVICE9	D3dDevice = GetDevice();

	loadModel(mPath);

	// 数値を初期化
	upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポインタ
	meshPoint = NULL;
	meshTexturePoint = NULL;

	// クラスポインタ
	material = new Material();

	// 頂点宣言
	D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	D3dDevice->CreateVertexDeclaration(planeDecl, &vertexDecl);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Model::~Model()
{
	// ポインタ
	RELEASE_POINT(meshPoint);
	RELEASE_CLASS_POINT(meshTexturePoint);

	// クラスポインタ
	RELEASE_CLASS_POINT(material);
}

//*****************************************************************************
//
// 上方向のベクトルにして回転
//
//*****************************************************************************
void Model::RotationVecUp(float angle)
{
	// 角度を記録する
	rot.y += angle;

	if (rot.y >= D3DXToRadian(360.0f))
	{
		rot.y = 0.0f;
	}
	if (rot.y <= D3DXToRadian(-360.0f))
	{
		rot.y = 0.0f;
	}

	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationAxis(&rotMatrix, &upVector, angle);					// 回転行列を作る
	D3DXVec3TransformCoord(&lookVector, &lookVector, &rotMatrix);	// カメラの新しい座標を計算する

	D3DXVec3Normalize(&lookVector, &lookVector);
	D3DXVec3Cross(&rightVector, &lookVector, &upVector);
	D3DXVec3Normalize(&rightVector, &rightVector);
	D3DXVec3Cross(&upVector, &rightVector, &lookVector);
	D3DXVec3Normalize(&upVector, &upVector);

	// OGL -> DX
	rightVector = -rightVector;
}

//*****************************************************************************
//
// ワールド変換を設定
//
//*****************************************************************************
void Model::SetWorldMatrix()
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&wMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&wMatrix, &wMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&wMatrix, &wMatrix, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&wMatrix, &wMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// モデルをロードする
//
//*****************************************************************************
HRESULT Model::loadModel(string const &mPath)
{
	Assimp::Importer import;																// Assimpのインポートを作る
	const aiScene *scene = import.ReadFile(mPath, /*aiProcess_Triangulate*/aiProcessPreset_TargetRealtime_Quality);	// ポリゴンを強制に三角形にする

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "[Error] Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

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
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());	// 取得したdiffuseMapsをallTextureの後ろに追加
		//vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "specularTexture");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());	// 取得したspecularMapsをallTextureの後ろに追加
		//vector<Texture> normalMaps = loadMaterialTexture(material, aiTextureType_HEIGHT, "normalTexture");
		//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());		// 取得したnormalMapsをallTextureの後ろに追加
		//vector<Texture> heightMaps = loadMaterialTexture(material, aiTextureType_AMBIENT, "heightTexture");
		//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());		// 取得したnormalMapsをallTextureの後ろに追加
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
vector<Texture> Model::loadMaterialTexture(aiMaterial *mat, aiTextureType mType, string typeName)
{
	vector<Texture> textures;	// 読み込んだテクスチャ

	for (unsigned int count = 0; count < mat->GetTextureCount(mType); count++)
	{
		aiString str;									// モデルから読み込まれたテクスチャファイルの名前
		mat->GetTexture(mType, count, &str);			// テクスチャパスを読み込み
		string path = "Resources/Texture/Hixo/Hixo" + string(str.C_Str());		// テクスチャの前にパスをつき

		bool skip = false;

		// もう読み込んだテクスチャならば、mTextureLoadedからもらう
		for (auto it : mTexturesLoaded)
		{
			if (strcmp(it.getTexPath().c_str(), path.c_str()) == 0)
			{
				textures.push_back(it);
				skip = true;
				break;
			}
		}

		// 新しいテクスチャならば読み込む
		if (!skip)
		{
			// テクスチャまだ読み込まなっかたら読み込む
			Texture texture(path.data());

			// テクスチャタイプ属性を切り捨てる(warning)

			// 読み込んだテクスチャを保存
			textures.push_back(texture);
			this->mTexturesLoaded.push_back(texture);
		}
	}

	return textures;
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
 // モデルを描画
 //
 //*****************************************************************************
void Model::draw()
{
	// 各メッシュを描画
	for (auto it : mMeshes)
	{
		//it.Draw();
	}

}