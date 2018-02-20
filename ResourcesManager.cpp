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
	this->textureList["skybox"] = "data/TEXTURE/skybox.jpg";

	this->textureList["cartoon"] = "data/TEXTURE/cartoon.png";
	this->textureList["edge"] = "data/TEXTURE/edge.png";

	this->textureList["fieldTransparent"] = "data/TEXTURE/field003.png";
	this->textureList["fieldSea"] = "data/TEXTURE/sea3k.png";
	this->textureList["fieldSea2"] = "data/TEXTURE/sea4.png";

	this->textureList["title"] = "data/TEXTURE/title3.png";
	this->textureList["press"] = "data/TEXTURE/press.png";
	this->textureList["ending"] = "data/TEXTURE/ending.png";

	this->textureList["shipBody"] = "data/TEXTURE/VikingShip/Ship.png";
	this->textureList["shipCannon"] = "data/TEXTURE/VikingShip/cannon_diffuse.png";

	this->textureList["bullet"] = "data/TEXTURE/bullet.png";

	this->textureList["UIminimap"] = "data/TEXTURE/UI/minimap.png";
	this->textureList["UIplayer"] = "data/TEXTURE/UI/player.png";
	this->textureList["UIenemy"] = "data/TEXTURE/UI/enemy.png";

	this->textureList["UIhp"] = "data/TEXTURE/UI/hp.png";

	this->textureList["UIpan"] = "data/TEXTURE/UI/pan.png";
	this->textureList["UIzen"] = "data/TEXTURE/UI/zen.png";
	this->textureList["UIstop"] = "data/TEXTURE/UI/stop.png";
	this->textureList["UIgou"] = "data/TEXTURE/UI/gou.png";

	this->textureList["UIleft"] = "data/TEXTURE/UI/left.png";
	this->textureList["UIright"] = "data/TEXTURE/UI/right.png";

	this->textureList["NULL"] = "NULL";

	// メッシュ検索マッピングを作る
	this->meshList["ship"] = "data/MODEL/PirateShip.x";
	this->meshList["ship2"] = "data/MODEL/ship2.x";
	this->meshList["shipCannon"] = "data/MODEL/Player_Cannon.x";
	this->meshList["shipBody"] = "data/MODEL/Player_Ship.x";
	this->meshList["ball"] = "data/MODEL/ball.x";
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
HRESULT ResourcesManager::LoadTexture(std::string name, LPDIRECT3DTEXTURE9* texturePoint)
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
				std::cout << "[Error] Loading Texture<" << name << "> Failed!" << std::endl;	// コンソールにメッセージを出す
				return E_FAIL;
			}
			else
			{
				std::cout << "[Information] Loading Texture<" << name << "> Success!" << std::endl;	// コンソールにメッセージを出す
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
std::string ResourcesManager::GetTextureStruct(std::string name)
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
HRESULT ResourcesManager::LoadMesh(std::string name, Model* model)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (GetMeshPath(name).c_str() != "NULL")
	{
		if (FAILED(D3DXLoadMeshFromX(			// Xファイルの読み込み
			GetMeshPath(name).c_str(),			// モデルのファイル名
			D3DXMESH_SYSTEMMEM,					// メッシュのメモリ確保オプション
			pDevice,							// デバイスへのポインタ
			NULL,								// 隣接性データを含むバッファへのポインタ
			&model->material->materialBuffer,// マテリアルデータを含むバッファへのポインタ
			NULL,								// エフェクトインスタンスを含むバッファへのポインタ
			&model->material->materialNum,	// マテリアル構造体の数
			&model->meshPoint)))				// メッシュへのポインタ
		{
			std::cout << "[Error] Loading Model<" << name << "> Failed!" << std::endl;
			return E_FAIL;
		}
		else
		{
			std::cout << "[Information] Loading Model<" << name << "> Success!" << std::endl;
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
			//std::string texPath = "data/TEXTURE/";
			//std::string texName = materials[count].pTextureFilename;
			//texPath += texName;

			// 初期化＆テクスチャを取得 & one textrue
			//model->this->meshTexturePoint[0] = NULL;
			//if (FAILED(D3DXCreateTextureFromFile(pDevice, texPath.c_str(), &model->this->meshTexturePoint[count])))
			//{
			//	std::cout << "[Error] Material's texture load Fail!" << std::endl;
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
std::string ResourcesManager::GetMeshPath(std::string name)
{
	if (this->meshList.find(name) != this->meshList.end())
	{
		return this->meshList[name];
	}

	return NULL;
}