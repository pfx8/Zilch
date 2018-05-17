//*****************************************************************************
//
// シーンマネジャー処理 [SceneManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Engine.h"
#include "input.h"

#include "..\Scene\Scene.h"
#include "..\Scene\Scene02.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneManager
{
private:
	unordered_map<string, Scene*>	mScenes;				// シーンマップ

public:
	Scene*							mCurrentScene;			// 今のシーンポインタ

	SceneManager();
	~SceneManager();

	void start();				// 最初のシーンを初期化
	void update();				// シーンを更新
	void draw();				// シーンを描画

	void addScene(string name, Scene* scene);		// シーンを増加
	HRESULT setActiveScene(string name);			// これから実行するシーンを選択
}; 

#endif // !_SCENE_MANAGER_H_

