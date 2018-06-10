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
	Camera* sysCamera = this->mParentGameObject->mParentScene->mSystemCamera;

	// �}�E�X����
	if (IsMouseRightPressed())
	{
		// �㉺�ړ�
		if (GetMouseY() > this->mIsMouseMoving)
		{
			// �v���X
			this->mCurrentLight->mLightPos -= sysCamera->mCameraUp * this->mMouseMoveSpeed;
		}
		
		if(GetMouseY() < -this->mIsMouseMoving)
		{
			// �}�C�i�X
			this->mCurrentLight->mLightPos += sysCamera->mCameraUp * this->mMouseMoveSpeed;
		}

		// �����ړ�
		if (GetMouseX() > this->mIsMouseMoving)
		{
			// �v���X
			this->mCurrentLight->mLightPos -= sysCamera->mCameraRight * this->mMouseMoveSpeed;
		}

		if (GetMouseX() < -this->mIsMouseMoving)
		{
			// �}�C�i�X
			this->mCurrentLight->mLightPos += sysCamera->mCameraRight * this->mMouseMoveSpeed;
		}

		// �}�E�X����̌��ʂ����C�g�ɓn��
		trans->mPos = this->mCurrentLight->mLightPos;
	}
}

//*****************************************************************************
//
// GUI�p�l��
//
//*****************************************************************************
void LightController::drawImGui(void)
{
	ImGui::TextUnformatted(u8"��������͍��̃f�o�b�O�E�C���h�E�ɏ����Ă���܂�");
}