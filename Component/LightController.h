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
#include "Camera.h"

#include "..\Engine\Engine.h"
#include "..\Engine\input.h"

#include "..\Scene\Scene.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class LightController : public Component
{
private:
	int				mIsMouseMoving = 2;
	float			mMoveSpeed = 0.1f;

public:
	Light*			mCurrentLight;

	LightController(void);
	~LightController(void);

	void update(void);
};

#endif // !_LIGHT_CONTROLLER_H_