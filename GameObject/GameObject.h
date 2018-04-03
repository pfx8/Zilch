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
	bool mActive = true;
	float mLastActiveTime = 0;

	GameObject();
	virtual ~GameObject();

};

#endif // !_GAME_OBJECT_H_
