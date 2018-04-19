//*****************************************************************************
//
// コンポーネントベースクラス [Component.h]
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
	virtual void start() {};
	virtual void update() {};

public:
	GameObject*			mGameObject;					// 所属GameObjectの他のコンポーネントを取れるように
	bool							mStart = false;						// スタートマック

	Component();
	virtual ~Component();
};

#endif // !_COMPONENT_H_
