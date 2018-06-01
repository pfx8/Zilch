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
PlayerController::PlayerController(void)
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
PlayerController::~PlayerController(void)
{

}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void PlayerController::update(void)
{
	// �v����\�̈ʒu�擾
	Transform* trans = this->mParentGameObject->getComponent<Transform>();

	// �V�X�e���J�������擾
	Camera* sysCamera = this->mParentGameObject->mScene->mSystemCamera;

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
