//*****************************************************************************
//
// GameObject [GameObject.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "..\Engine\Engine.h"

class GameObject
{
private:
	void start();
	void update();

public:
	bool active = true;
	float lastActiveTime = 0;

	GameObject();
	virtual ~GameObject();

};

#endif // !_GAME_OBJECT_H_
