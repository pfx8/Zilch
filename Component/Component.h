//*****************************************************************************
//
// �R���|�[�l���g�x�[�X�N���X [Component.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "../Engine/Engine.h"
#include "../GameObject/GameObject.h"

class Component
{
	friend class GameObject;
private:
	virtual void start() {};
	virtual void update() {};

public:
	GameObject*			mGameObject;					// ����GameObject�̑��̃R���|�[�l���g������悤��
	bool							mStart = false;						// �X�^�[�g�}�b�N

	Component();
	virtual ~Component();
};

#endif // !_COMPONENT_H_
