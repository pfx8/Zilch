//*****************************************************************************
//
// ライトコントローラ処理 [LightController.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _LIGHT_CONTROLLER_H_
#define _LIGHT_CONTROLLER_H_

#include "Component.h"
#include "Light.h"

#include "..\Engine\Engine.h"
#include "..\Engine\input.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class LightController : public Component
{
private:
	int					mMouseIsMoving = 2;			// マウスの移動チェック量

	void update();

public:
	Light*				mLight;						// 操作するライト

	LightController();
	~LightController();
};

#endif // !_LIGHT_CONTROLLER_H_