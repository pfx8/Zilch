﻿//*****************************************************************************
//
// シーンマネジャー処理 [SceneManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SceneManager.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SceneManager::SceneManager()
{

}

//*****************************************************************************
//
// 最初のシーンを初期化
//
//*****************************************************************************
void SceneManager::start()
{
	// 各シーンのポイントを初期化
	Scene02* zilch = new Scene02();
	addScene("zilch", zilch);

	// 最初のシーンを選択
	setActiveScene("zilch");
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SceneManager::~SceneManager()
{
	// to do delete unordered_map
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void SceneManager::update()
{
	if (this->mCurrentScene->mIsStart)
	{
		this->mCurrentScene->update();
	}
	else
	{
		this->mCurrentScene->start();
		this->mCurrentScene->mIsStart = true;
	}
}

//*****************************************************************************
//
// シーンの描画
//
//*****************************************************************************
void SceneManager::draw()
{
	// シーンを描画
	this->mCurrentScene->draw();
}

//*****************************************************************************
//
// シーンを増加
//
//*****************************************************************************
void SceneManager::addScene(string name, Scene* scene)
{
	mScenes.insert({ name, scene });
}

//*****************************************************************************
//
// これから実行するシーンを選択
//
//*****************************************************************************
HRESULT SceneManager::setActiveScene(string name)
{
	if (mScenes.find(name) != mScenes.end())
	{
		this->mCurrentScene = mScenes[name];

		return S_OK;
	}

	// Debugウインドへ
	cout << "[Error] <Scene> Set " << name << " ... failed!" << endl;

	return E_FAIL;
}