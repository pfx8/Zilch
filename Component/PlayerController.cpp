//*****************************************************************************
//
// �v���[���R���g���[�� [PlayerControllers.cpp]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#include "PlayerController.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
PlayerController::PlayerController()
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
PlayerController::~PlayerController()
{

}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void PlayerController::update()
{
	// �v����\�̈ʒu�擾
	Transform* trans = this->mGameObject->getComponent<Transform>();

	// �V�X�e���J�������擾
	Camera* sysCamera = this->mGameObject->mScene->mSystemCamera;

	// �}�E�X����
	if (IsMouseRightPressed())
	{
		// �㉺�ړ�
		if (GetMouseY() > this->mMouseIsMoving)
		{
			// �v���X
			trans->mPos -= sysCamera->mCameraUp * this->mMoveSpeed;
		}

		if (GetMouseY() < -this->mMouseIsMoving)
		{
			// �}�C�i�X
			trans->mPos += sysCamera->mCameraUp * this->mMoveSpeed;
		}

		// �����ړ�
		if (GetMouseX() > this->mMouseIsMoving)
		{
			// �v���X
			trans->mPos -= sysCamera->mCameraRight * this->mMoveSpeed;
		}

		if (GetMouseX() < -this->mMouseIsMoving)
		{
			// �}�C�i�X
			trans->mPos += sysCamera->mCameraRight * this->mMoveSpeed;
		}
	}
}
