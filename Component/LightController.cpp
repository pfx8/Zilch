//*****************************************************************************
//
// ���C�g�R���g���[������ [LightController.cpp]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#include "LightController.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
LightController::LightController()
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
LightController::~LightController()
{

}

//*****************************************************************************
//
// �R���g���[���X�V
//
//*****************************************************************************
void LightController::update()
{
	Transform* trans = this->mLight->mGameObject->getComponent<Transform>();

	if (IsMouseCenterPressed())
	{
		// �㉺�ړ�
		if (GetMouseY() > this->mMouseIsMoving)
		{
			// �v���X
			this->mLight->mLightPos.y -= 0.5;
		}
		
		if(GetMouseY() < -this->mMouseIsMoving)
		{
			// �}�C�i�X
			this->mLight->mLightPos.y += 0.5;
		}

		// �����ړ�
		if (GetMouseX() > this->mMouseIsMoving)
		{
			// �v���X
			this->mLight->mLightPos.x -= 0.5;
		}

		if (GetMouseX() < -this->mMouseIsMoving)
		{
			// �}�C�i�X
			this->mLight->mLightPos.x += 0.5;
		}

		trans->mPos = this->mLight->mLightPos;
	}
}