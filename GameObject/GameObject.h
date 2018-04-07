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
	bool			mActive = true;						// 使ってるマーク
	float		mLastActiveTime = 0;			// 前回更新した時間

	GameObject();
	virtual ~GameObject();

	// 任意コンポーネントを追加できるようにテンプレートを使った
	// ここのtypenameはComponentクラスまたそれの継承クラス
	template<typename T> void addComponent(string name, T* t)
	{
		mComponents.push_back(t);
		mComponentsMap.insert({ name, t });
	}

	// 名前によってコンポーネント取得
	// ここのtypenameはComponentクラスまたそれの継承クラス
	template<typename T> T* getComponent(string name)
	{
		if (mComponentsMap.find(name) != mComponentsMap.end())
		{
			//------------------------------------------------------------
			// dynamic_cast<type*>(e)
			// typeは必ずクラス型、eは必ずポインタ(nullptrはダメ)
			//
			// 重要 : eは必ずtypeクラス型かtypeの継承クラス型
			//
			// 戻り値 : eのクラス型のポインタ
			//------------------------------------------------------------
			return dynamic_cast<T*>(mComponentsMap[name]);
		}

		cout << "[Error] <Component> Get " << name << " failed!" << endl;
		return nullptr;
	}
};

#endif // !_GAME_OBJECT_H_
