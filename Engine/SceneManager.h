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
//#include "..\Scene\Scene01.h"
#include "..\Scene\Scene02.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneManager
{
private:
	string mCurrentScene;				// 今のシーンの名前
	map<string, Scene*> mScenes;

public:
	SceneManager();
	~SceneManager();

	void update();			// シーンを更新
	void draw();			// シーンを描画

	void addScene(string name, Scene* scene);	// シーンを増加
	void setActiveScene(string name);			// 名前によってシーンを交替
}; 

#endif // !_SCENE_MANAGER_H_

