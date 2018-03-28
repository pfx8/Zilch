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
	this->textureList["skybox"] = "Data/Texture/skybox.jpg";
	this->textureList["field"] = "Data/Texture/field.jpg";
	this->textureList["fieldNor"] = "Data/Texture/fieldNor.jpg";
	this->textureList["NULL"] = "NULL";

	// メッシュ検索マッピングを作る
	this->meshList["woman"] = "Data/Model/woman.x";
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
	if(this->textureList.find(name) != this->textureList.end())
	{
		return this->textureList[name];
	}
}

//*****************************************************************************
//
// メッシュを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadMesh(string name, Model* model)
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
			// テクスチャは一枚なので、ここではよみこまない。モデル初期化する時一回で読み込み

			// テクスチャパスの前に"data/TEXTURE/"を添付
			//string texPath = "data/TEXTURE/";
			//string texName = materials[count].pTextureFilename;
			//texPath += texName;

			// 初期化＆テクスチャを取得 & one textrue
			//model->this->meshTexturePoint[0] = NULL;
			//if (FAILED(D3DXCreateTextureFromFile(pDevice, texPath.c_str(), &model->this->meshTexturePoint[count])))
			//{
			//	cout << "[Error] Material's texture load Fail!" << endl;
			//	return E_FAIL;
			//}


		}
	}

	// ッシュの面および頂点の順番変更を制御し、パフォーマンスを最適化する
	model->meshPoint->OptimizeInplace(D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL);

	return S_OK;
}

//*****************************************************************************
//
// メッシュパスを取得
//
//*****************************************************************************
string ResourcesManager::GetMeshPath(string name)
{
	if (this->meshList.find(name) != this->meshList.end())
	{
		return this->meshList[name];
	}

	return NULL;
}