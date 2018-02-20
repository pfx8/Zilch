//*****************************************************************************
//
// シーン処理 [Scene.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene::Scene()
{	
	this->resourcesManager = new ResourcesManager;	// リソース
	this->message = new DebugMessage;

	// テクスチャを読み込み
	// this->resourcesManager->InitTexture();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene::~Scene()
{
	// クラスポインタ
	// リソース
	RELEASE_CLASS_POINT(this->resourcesManager);
	RELEASE_CLASS_POINT(this->message);
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Scene::SetWorldMatrix(D3DXMATRIX* worldMatrix, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(worldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(worldMatrix, worldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(worldMatrix, worldMatrix, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(worldMatrix, worldMatrix, &mtxTranslate);
}

