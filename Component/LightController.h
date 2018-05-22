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

#include "..\Engine\Engine.h"
#include "..\Engine\input.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class LightController : public Component
{
private:
	int					mMouseIsMoving = 2;			// �}�E�X�̈ړ��`�F�b�N��

	void update();

public:
	Light*				mLight;						// ���삷�郉�C�g

	LightController();
	~LightController();
};

#endif // !_LIGHT_CONTROLLER_H_