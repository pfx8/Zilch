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

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class GameObject
{
	friend class Scene;
	friend class GUI;

private:
	// typeid(classPoint)を利用して各componentのtype_indexを取得、そしてマップに保存
	map<type_index, Component*>		mComponentsMap;

	void start(void);
	void update(void);

public:
	Scene*			mScene;							// シーンポインタ
	bool			mDraw = false;					// 描画マーク
	bool			mActive = true;					// 使ってるマーク
	float			mLastActiveTime = 0;			// 前回更新した時間

	GameObject(void);
	virtual ~GameObject(void);

	//*****************************************************************************
	//
	// 任意ComponentをGameObjectに入れる
	//
	// ここの<typename T>はComponentクラスの継承クラス
	//
	//*****************************************************************************
	template<typename T> void addComponent(T* component)
	{
		// 添付したいコンポーネントの中に所属GameObjectのポインタを入れる
		component->mParentGameObject = this;

		// MeshRenderがあればGameObjectを描画
		if (typeid(T) == typeid(MeshRender))
		{
			this->mDraw = true;
		}

		mComponentsMap.insert({ typeid(T), component });
	}

	//*****************************************************************************
	//
	// クラスタイプによってComponentを戻る
	//
	// ここの<typename T>はComponentの継承クラス
	//
	// <説明> dynamic_cast<type*>(e)
	// typeは必ずクラス型、eは必ずポインタ(nullptrはダメ)
	// eは必ずtypeクラス型かtypeの継承クラス型
	// そしてベースクラスの中にポリモーフィックな型が必要
	// <戻り値> eのクラス型のポインタ
	//
	//*****************************************************************************
	template<typename T> T* getComponent()
	{
		if (this->mComponentsMap.find(typeid(T)) != this->mComponentsMap.end())
		{
			return dynamic_cast<T*>(this->mComponentsMap[typeid(T)]);
		}

		cout << "[Error] <Component> Get " << typeid(T).name() << " failed!" << endl;
		return nullptr;
	}
};

#endif // !_GAME_OBJECT_H_
