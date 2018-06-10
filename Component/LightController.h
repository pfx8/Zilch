//*****************************************************************************
//
// ���C�g�R���g���[������ [LightController.h]
//
// Author : �����E�@�J���V��
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
// �N���X�錾
//
//*****************************************************************************
class LightController : public Component
{
private:
	int				mIsMouseMoving = 2;
	float			mMouseMoveSpeed = 0.1f;

public:
	Light*			mCurrentLight;

	LightController(void);
	~LightController(void);

	void update(void);
	void drawImGui(void);
};

#endif // !_LIGHT_CONTROLLER_H_