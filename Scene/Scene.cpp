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
Scene::Scene(void)
{	
	// BGカラー初期化
	this->mBGColor = D3DXVECTOR4(0.4, 0.4, 0.4, 1.0);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene::~Scene(void)
{
	// コンテナをリリース
	vector<MeshRender*>().swap(mMeshRenders);
	this->mGameObjects.clear();

	RELEASE_CLASS_POINT(this->mSystemCamera);
}

//*****************************************************************************
//
// シーンにGameObjectを添付
//
//*****************************************************************************
void Scene::addGameObject(wstring name, GameObject* gameObject)
{
	gameObject->mParentScene = this;

	this->mGameObjects.insert({ name, gameObject });
}

//*****************************************************************************
//
// シーンからGameObjectを取得
//
//*****************************************************************************
GameObject* Scene::getGameObject(wstring name)
{
	if (this->mGameObjects.find(name) != this->mGameObjects.end())
	{
		return this->mGameObjects[name];
	}

	// Debugウインドへ
	wcout << "<Error> [GameObject] Get " << name << " failed!" << endl;

	return nullptr;
}

//*****************************************************************************
//
// シーンの更新
//
//*****************************************************************************
void Scene::update(void)
{
	// 各GameObjectを更新
	for (auto it : this->mGameObjects)
	{
		if (it.second->mIsActive == true)
		{
			it.second->update();
		}
	}

	// 使っているカメラ更新
	this->mCurrentCamera->update();
}

//*****************************************************************************
//
// シーンの描画
//
//*****************************************************************************
void Scene::draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(this->mBGColor.x, this->mBGColor.y, this->mBGColor.z, this->mBGColor.w), 1.0f, 0);
	//シャドウマップ
	for (auto it : mMeshRenders)
	{
		if (it->mIsStart == true)
		{
			if (it->mIsDrawShadow == true)
			{
				it->drawShadowMap();
			}
		}
	}

	// バックバッファ＆Ｚバッファのクリア
	getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(this->mBGColor.x, this->mBGColor.y, this->mBGColor.z, this->mBGColor.w), 1.0f, 0);
	// メッシュ
	for (auto it : mMeshRenders)
	{
		if (it->mIsStart == true)
		{
			it->drawGameObject();
		}
	}
}