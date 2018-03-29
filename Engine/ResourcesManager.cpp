//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ResourcesManager.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ResourcesManager::ResourcesManager()
{
	// テクスチャ検索マッピングを作る
	this->textures["skybox"] = "Resources/Texture/skybox.jpg";
	this->textures["field"] = "Resources/Texture/field.jpg";
	this->textures["fieldNor"] = "Resources/Texture/fieldNor.jpg";
	this->textures["NULL"] = "NULL";

	// メッシュ検索マッピングを作る
	this->meshes["woman"] = "Resources/Model/woman.x";
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ResourcesManager::~ResourcesManager()
{

}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadTexture(string name, LPDIRECT3DTEXTURE9* texturePoint)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (*texturePoint == NULL)
	{
		if (GetTextureStruct(name).data() != "NULL")
		{
			// テクスチャを読み込み
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				GetTextureStruct(name).c_str(),
				texturePoint)))
			{
				cout << "[Error] Loading <Texture> " << name << " ... Fail!" << endl;	// コンソールにメッセージを出す
				return E_FAIL;
			}
			else
			{
				cout << "[Information] Loading <Texture> " << name << " ... Success!" << endl;	// コンソールにメッセージを出す
				return S_OK;
			}
		}
		else
		{
			*texturePoint = NULL;
			return S_OK;
		}
	}
}


//*****************************************************************************
//
// テクスチャ構造体を取得
//
//*****************************************************************************
string ResourcesManager::GetTextureStruct(string name)
{
	if(this->textures.find(name) != this->textures.end())
	{
		return this->textures[name];
	}
}

//*****************************************************************************
//
// メッシュを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadModel(string name, Model* model)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (GetMeshPath(name).c_str() != "NULL")
	{
		if (FAILED(D3DXLoadMeshFromX(			// Xファイルの読み込み
			GetMeshPath(name).c_str(),			// モデルのファイル名
			D3DXMESH_SYSTEMMEM,					// メッシュのメモリ確保オプション
			pDevice,							// デバイスへのポインタ
			NULL,								// 隣接性データを含むバッファへのポインタ
			&model->material->materialBuffer,	// マテリアルデータを含むバッファへのポインタ
			NULL,								// エフェクトインスタンスを含むバッファへのポインタ
			&model->material->materialNum,		// マテリアル構造体の数
			&model->meshPoint)))				// メッシュへのポインタ
		{
			cout << "[Error] Loading <Model> " << name << " ... Fail!" << endl;
			return E_FAIL;
		}
		else
		{
			cout << "[Information] Loading <Model> " << name << " ... Success!" << endl;
		}
	}

	// マテリアルの数によってマテリアルを格納できるメモリを確保
	model->material->materialPoint = new D3DMATERIAL9[model->material->materialNum];

	// テクスチャは一枚なので、ここではよみこまない。モデル初期化する時一回で読み込み
	// マテリアルの数によってテクスチャを格納できるメモリを確保
	//model->this->meshTexturePoint = new LPDIRECT3DTEXTURE9[model->this->material->this->materialNum];

	// Xファイルに保存されているマテリアル情報構造体
	D3DXMATERIAL* materials = (D3DXMATERIAL*)model->material->materialBuffer->GetBufferPointer();

	for (DWORD count = 0; count < model->material->materialNum; count++)
	{
		// マテリアルのプロパティをコピー
		model->material->materialPoint[count] = materials[count].MatD3D;

		// アンビエント色をディフューズ色にする
		//model->this->material->this->materialPoint[count].Ambient = model->this->material->this->materialPoint[count].Diffuse;

		// Xファイルの情報によってすべてのテクスチャを読み込み
		if (materials[count].pTextureFilename != NULL)
		{

		}
	}

	// ッシュの面および頂点の順番変更を制御し、パフォーマンスを最適化する
	model->meshPoint->OptimizeInplace(D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL);

	return S_OK;
}

//*****************************************************************************
//
// Assimpでモデルを読み込み
//
//*****************************************************************************
void ResourcesManager::LoadModel(string name, const char *path)
{
	this->models.insert({name, new Model(path) }); // モデルを名前とデータをペアにする
}

//*****************************************************************************
//
// モデルを名前によってゲット
//
//*****************************************************************************
Model* ResourcesManager::GetModel(string name)
{
	if(this->models.find(name) != this->models.end())
	{
		return this->models[name];
	}

	return nullptr;
}

//*****************************************************************************
//
// メッシュパスを取得
//
//*****************************************************************************
string ResourcesManager::GetMeshPath(string name)
{
	if (this->meshes.find(name) != this->meshes.end())
	{
		return this->meshes[name];
	}

	return NULL;
}