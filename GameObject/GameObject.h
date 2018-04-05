//*****************************************************************************
//
// GameObject [GameObject.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "../Engine/Engine.h"
#include "../Component/Component.h"

class GameObject
{
	friend class Scene;

private:
	vector<Component*>									mComponents;				// コンポーネントコンテナ
	unordered_map<string, Component*>		mComponentsMap;		// 名前つきのコンポーネントマップ

	void start();
	void update();

public:
	bool mActive = true;
	bool mIsDraw = false;
	float mLastActiveTime = 0;

	GameObject();
	virtual ~GameObject();

	template<typename T> void addComponent(string name, T* t);			// 任意コンポーネントを追加できるようにテンプレートを使った
	template<typename T> T* getComponent(string name);						// 名前によってコンポーネント取得
};

#endif // !_GAME_OBJECT_H_
