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
	// �h��Ԃ����[�h
	if (GetKeyboardPress(DIK_1))			// key 1
	{
		// ���C���t���[����h��Ԃ�
		getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		cout << "[Information] <RenderState> ... WIREFRAME" << endl;	// �R���\�[���Ƀ��b�Z�[�W���o��
	}
	if (GetKeyboardPress(DIK_2))			// key 2
	{
		// �ʂ�h��Ԃ�
		getDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		cout << "[Information] <RenderState> ... SOLID" << endl;	// �R���\�[���Ƀ��b�Z�[�W���o��
	}
}
