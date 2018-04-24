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
	mMessage = new DebugMessage;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene::~Scene()
{
	RELEASE_CLASS_POINT(this->mMessage);
}

//*****************************************************************************
//
// シーンにGameObjectを添付
//
//*****************************************************************************
void Scene::addGameObject(string name, GameObject* gameObject)
{
	gameObject->mScene = this;
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

//*****************************************************************************
//
// シーンの更新
//
//*****************************************************************************
void Scene::update()
{
	for (auto it : mGameObjectMap)
	{
		if (it.second->mActive == true)
		{
			it.second->update();
		}
	}
}

//*****************************************************************************
//
// シーンの描画
//
//*****************************************************************************
void Scene::draw()
{
	// バックバッファ＆Ｚバッファのクリア
	getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(155, 255, 255, 255), 1.0f, 0);
	//シャドウマップ
	for (auto it : mMeshRenders)
	{
		if (it->mStart == true)
		{
			if (it->mIsDrawShadow == true)
			{
				it->drawShadowMap();
			}
		}
	}

	// バックバッファ＆Ｚバッファのクリア
	getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(155, 255, 255, 255), 1.0f, 0);
	// メッシュ
	for (auto it : mMeshRenders)
	{
		if (it->mStart == true)
		{
			it->draw();
		}
	}
}