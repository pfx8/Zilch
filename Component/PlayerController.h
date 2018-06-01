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
	int					mMouseIsMoving = 2;			// マウスの移動チェック量
	float				mMoveSpeed = 0.1f;			// ライト移動スピード

	void update(void);

public:

	PlayerController(void);
	~PlayerController(void);
};

#endif // !_PLAYER_CONTROLLERS_H_