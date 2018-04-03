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

class Component
{
private:
	virtual void start();
	virtual void update();

public:
	bool		mActive = true;
	float		mLastActiveTime = 0;

	Component();
	virtual ~Component();

};

#endif // !_COMPONENT_H_
