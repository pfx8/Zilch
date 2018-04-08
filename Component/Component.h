//*****************************************************************************
//
// Component [Component.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "../Engine/Engine.h"
#include "../GameObject/GameObject.h"

class Component
{
	friend class GameObject;
private:
	virtual void start();
	virtual void update();

public:
	bool							mActive = true;					// 使ってるかどうかマーク
	float						mLastActiveTime = 0;		// 前回更新した時間
	GameObject*			mGameObject;					// 所属GameObjectの他のコンポーネントを取れるように

	Component();
	virtual ~Component();
};

#endif // !_COMPONENT_H_
