//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "..\Component\Camera.h"
#include "..\Component\CameraController.h"
#include "..\Component\Component.h"
#include "..\Component\MeshRender.h"
#include "..\Component\PlayerController.h"
#include "..\Component\Transform.h"
#include "..\Component\LightController.h"
#include "..\Component\Light.h"

#include "..\Engine\Engine.h"
#include "..\Engine\input.h"
#include "..\Engine\Shader.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:

public:
	string									mName;					// シーンの名前
	D3DXVECTOR4								mBGColor;				// 背景カラー
	bool									mIsStart;				// スタートマーク
	vector<MeshRender*>						mMeshRenders;			// メッシュレンダリング
	map<wstring, GameObject*>				mGameObjectMap;			// 取得するために作ったGameObjectのマップ

	Camera*									mSystemCamera;			// システムカメラ
	Camera*									mCurrentCamera;			// 使っているカメラ
	Shader*									mShader;				// 現在レンダリング用なシェーダー

	Scene(void);
	~Scene(void);

	virtual void start(void) {};		// シーンのスタート
	void update(void);					// シーンの更新
	void draw(void);					// シーンの描画
	
	void addGameObject(wstring name, GameObject* gameObject);		// シーンにGameObjectを増加
	GameObject* getGameObject(wstring name);							// シーンからGameObjectを取得
};
#endif // !_SCENE_H_

