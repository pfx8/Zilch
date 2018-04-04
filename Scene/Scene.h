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
#include "../Engine/Engine.h"
#include "../Engine/input.h"
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
	Resources*			mResources;		// リソース
	DebugMessage*		message;		// メッセージ
	bool				mIsStart;
	
	map<string, GameObject*> mGameObjects;	// シーンの中にすべてのgameObjectを保存

	Scene();
	~Scene();

	virtual void start() {};			// シーンのスタート
	virtual void update() {};			// シーンの更新
	virtual void draw() {};				// シーンの描画

	// ワールド変換
	void SetWorldMatrix(D3DXMATRIX* wMatrix, D3DXVECTOR3 pos=D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3 rot=D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 scl=D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	// シーンにGameObjectを増加
	void addGameObject(string name, GameObject* gameObject)
	{
		mGameObjects.insert({ name, gameObject });
	}

	// シーンからGameObjectを取得
	GameObject* getGameObject(string name)
	{
		if (mGameObjects.find(name) != mGameObjects.end())
		{
			return mGameObjects[name];
		}

		cout << "[Error] <GameObject> Get " << name << " failed!" << endl;
		return nullptr;
	}
};

#endif // !_SCENE_H_

