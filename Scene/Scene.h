//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Component/Camera.h"
#include "../Component/CameraController.h"
#include "../Component/Component.h"
#include "../Component/MeshRender.h"
#include "../Component/PlayerController.h"
#include "../Component/Transform.h"
#include "../Component/Light.h"
#include "../Engine/Engine.h"
#include "../Engine/input.h"
#include "../Engine/DebugMessage.h"
#include "../GameObject/GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:

public:
	DebugMessage*				mMessage;		// メッセージ
	bool						mIsStart;		// スタートマーク

	vector<MeshRender*>								mMeshRenders;			// メッシュレンダリング
	unordered_map<string, GameObject*>				mGameObjectMap;			// 取得するために作ったGameObjectのマップ

	Scene();
	~Scene();

	virtual void start() {};			// シーンのスタート

	void update();						// シーンの更新
	void draw();						// シーンの描画
	
	void addGameObject(string name, GameObject* gameObject);		// シーンにGameObjectを増加
	GameObject* getGameObject(string name);							// シーンからGameObjectを取得
};
#endif // !_SCENE_H_

