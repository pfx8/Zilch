//*****************************************************************************
//
// コンポーネントベースクラス [Component.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "..\Engine\Engine.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Component
{
	friend class GameObject;

private:

public:
	GameObject*			mParentGameObject;			// 所属のGameObjectポインタ
	bool				mIsStart = false;			// スタートマック

	Component(void);
	virtual ~Component(void);

	virtual void start(void) {};
	virtual void update(void) {};
	virtual void drawImGui(void) {};
};

#endif // !_COMPONENT_H_
