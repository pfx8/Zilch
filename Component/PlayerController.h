//*****************************************************************************
//
// プレーヤコントローラ [PlayerController.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _PLAYER_CONTROLLERS_H_
#define _PLAYER_CONTROLLERS_H_

#include "Component.h"
#include "../Engine/Engine.h"
#include "../Engine/input.h"

class PlayerController : public Component
{
private:
	void update();

public:

	PlayerController();
	~PlayerController();
};

#endif // !_PLAYER_CONTROLLERS_H_