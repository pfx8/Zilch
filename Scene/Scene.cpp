//*****************************************************************************
//
// シーン処理 [Scene.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene::Scene()
{	
	mResources = new Resources;	// リソース
	message = new DebugMessage;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene::~Scene()
{
	// リソース
	RELEASE_CLASS_POINT(this->mResources);
	RELEASE_CLASS_POINT(this->message);
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Scene::SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(wMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(wMatrix, wMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(wMatrix, wMatrix, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(wMatrix, wMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// シーンにGameObjectを添付
//
//*****************************************************************************
void Scene::addGameObject(string name, GameObject* gameObject)
{
	if (name == "meshRender")
	{
		mMeshRenders.push_back(gameObject->getComponent<MeshRender>("meshRender"));
	}
	mGameObjectMap.insert({ name, gameObject });
}

//*****************************************************************************
//
// シーンからGameObjectを取得
//
//*****************************************************************************
GameObject* Scene::getGameObject(string name)
{
	if (mGameObjectMap.find(name) != mGameObjectMap.end())
	{
		return mGameObjectMap[name];
	}
	cout << "[Error] <GameObject> Get " << name << " failed!" << endl;
	return nullptr;
}