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
LightController::LightController(void)
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
LightController::~LightController(void)
{

}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void LightController::update(void)
{
	// ���C�g�ʒu�擾
	Transform* trans = this->mCurrentLight->mParentGameObject->getComponent<Transform>();

	// �V�X�e���J�������擾
	Camera* sysCamera = this->mParentGameObject->mScene->mSystemCamera;

	// �}�E�X����
	if (IsMouseCenterPressed())
	{
		// �㉺�ړ�
		if (GetMouseY() > this->mIsMouseMoving)
		{
			// �v���X
			this->mCurrentLight->mLightPos -= sysCamera->mCameraUp * this->mMoveSpeed;
		}
		
		if(GetMouseY() < -this->mIsMouseMoving)
		{
			// �}�C�i�X
			this->mCurrentLight->mLightPos += sysCamera->mCameraUp * this->mMoveSpeed;
		}

		// �����ړ�
		if (GetMouseX() > this->mIsMouseMoving)
		{
			// �v���X
			this->mCurrentLight->mLightPos -= sysCamera->mCameraRight * this->mMoveSpeed;
		}

		if (GetMouseX() < -this->mIsMouseMoving)
		{
			// �}�C�i�X
			this->mCurrentLight->mLightPos += sysCamera->mCameraRight * this->mMoveSpeed;
		}

		// �}�E�X����̌��ʂ����C�g�ɓn��
		trans->mPos = this->mCurrentLight->mLightPos;
	}
}