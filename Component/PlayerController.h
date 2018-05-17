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
#include "MeshRender.h"

#include "..\Engine\Engine.h"
#include "..\Engine\input.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class PlayerController : public Component
{
private:
	void update();

public:

	PlayerController();
	~PlayerController();
};

#endif // !_PLAYER_CONTROLLERS_H_