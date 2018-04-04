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
#include "../Scene/Scene.h"
#include "../Component/Component.h"

class GameObject
{
	friend class Scene;

private:
	vector<Component*>			mComponents;		// コンポーネントコンテナ
	map<string, Component*>		mComponentsMap;		// 名前つきのコンポーネントマップ

	void start();
	void update();

public:
	bool mActive = true;
	float mLastActiveTime = 0;

	GameObject();
	virtual ~GameObject();

	// 任意コンポーネントを追加できるようにテンプレートを使った
	// ここのtypenameはComponentクラスまたそれの継承クラス
	template<typename T>
	void addComponent(string name, T* t)
	{
		mComponents.push_back(t);
		mComponentsMap.insert({name, t});
	}

	template<typename T>
	T* getComponent(string name)
	{
		if (mComponentsMap.find(name) != mComponentsMap.end())
		{
			return mComponentsMap.find(name);
		}

		cout << "[Error] <Component> Get " << name << " failed!" << endl;
		return nullptr;
	}
};

#endif // !_GAME_OBJECT_H_
