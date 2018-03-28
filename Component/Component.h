//*****************************************************************************
//
// Component [Component.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "..\Engine\Engine.h"

class Component
{
private:
	virtual void start();
	virtual void update();

public:
	bool active = true;
	float lastActiveTime = 0;

	Component();
	virtual ~Component();

};

#endif // !_COMPONENT_H_
