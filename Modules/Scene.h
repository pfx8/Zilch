//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "FbxSDK.h"
#include "..\Engine.h"
#include "..\ResourcesManager.h"
#include "..\DebugMessage.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:

public:
	ResourcesManager*		m_resourcesManager;	// リソースマネジメント
	DebugMessage*		m_message;		// メッセージ
	FBX_SDK*				m_fbxSdk;		// FbxSDK
	
	Scene();
	~Scene();

	virtual void Update() {};		// 仮想関数
	virtual void Draw() {};		// 仮想関数
	virtual void Control() {};	// プレーヤー操作関数
	virtual void SetRenderState() {};		// レンダリング状態を設定
	virtual bool FromFbxSceneToScene();	// fbxSDkによって読み込んだデータを自分のSceneクラスに入れる
};

#endif // !_SCENE_H_

