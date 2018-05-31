//*****************************************************************************
//
// �v���[���R���g���[�� [PlayerController.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _PLAYER_CONTROLLERS_H_
#define _PLAYER_CONTROLLERS_H_

#include "Component.h"
#include "MeshRender.h"

#include "..\Engine\Engine.h"
#include "..\Engine\input.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class PlayerController : public Component
{
private:
	int					mMouseIsMoving = 2;			// �}�E�X�̈ړ��`�F�b�N��
	float				mMoveSpeed = 0.1f;			// ���C�g�ړ��X�s�[�h

	void update();

public:

	PlayerController();
	~PlayerController();
};

#endif // !_PLAYER_CONTROLLERS_H_