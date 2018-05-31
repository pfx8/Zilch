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
	// ���C�g�ʒu�擾
	Transform* trans = this->mLight->mGameObject->getComponent<Transform>();

	// �V�X�e���J�������擾
	Camera* sysCamera = this->mGameObject->mScene->mSystemCamera;

	// �}�E�X����
	if (IsMouseCenterPressed())
	{
		// �㉺�ړ�
		if (GetMouseY() > this->mMouseIsMoving)
		{
			// �v���X
			this->mLight->mLightPos -= sysCamera->mCameraUp * this->mMoveSpeed;
		}
		
		if(GetMouseY() < -this->mMouseIsMoving)
		{
			// �}�C�i�X
			this->mLight->mLightPos += sysCamera->mCameraUp * this->mMoveSpeed;
		}

		// �����ړ�
		if (GetMouseX() > this->mMouseIsMoving)
		{
			// �v���X
			this->mLight->mLightPos -= sysCamera->mCameraRight * this->mMoveSpeed;
		}

		if (GetMouseX() < -this->mMouseIsMoving)
		{
			// �}�C�i�X
			this->mLight->mLightPos += sysCamera->mCameraRight * this->mMoveSpeed;
		}

		// �}�E�X��������C�gGUI�ɍX�V
		trans->mPos = this->mLight->mLightPos;
	}
}