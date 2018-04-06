//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Component/Component.h"
#include "../Component/MeshRender.h"
#include "../Engine/Engine.h"
#include "../Engine/input.h"
#include "../Engine/Light.h"
#include "../Engine/Resources.h"
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
	// シーンの正方向ベクトルを初期化
	D3DXVECTOR3			mSceneFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3			mSceneUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3			mSceneRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	Resources*					mResources;		// リソース
	DebugMessage*		message;				// メッセージ
	bool								mIsStart;

	unordered_map<string, GameObject*> mGameObjects;			// シーンの中にすべてのgameObjectを保存
	vector<MeshRender*>								mMeshRenders;			// 描画メッシュ集合
	vector<Light*>											mLights;						// ライト集合


	Scene();
	~Scene();

	virtual void start() {};				// シーンのスタート
	virtual void update() {};			// シーンの更新
	virtual void draw() {};				// シーンの描画

	// ワールド変換
	void SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	void addGameObject(string name, GameObject* gameObject);		// シーンにGameObjectを増加
	GameObject* getGameObject(string name);										// シーンからGameObjectを取得
};

#endif // !_SCENE_H_

