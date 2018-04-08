﻿//*****************************************************************************
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
	message = new DebugMessage;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene::~Scene()
{
	RELEASE_CLASS_POINT(this->message);
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
		//cout << "<Test> : [" << it.first  << "]" << endl;
		if (it.second->mActive == true)
		{
			//cout << "<Draw GameObject> : [" << it.first  << "]" << endl;
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
	for (auto it : mGameObjectMap)
	{
		//cout << "<Test> : [" << it.first  << "]" << endl;
		if (it.second->mDraw == true)
		{
			//cout << "<Draw GameObject> : [" << it.first  << "]" << endl;
			it.second->getComponent<MeshRender>("meshRender")->draw();
		}
	}
}