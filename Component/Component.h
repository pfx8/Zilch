//*****************************************************************************
//
// Component [Component.h]
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
	virtual void start();
	virtual void update();

public:
	bool							mActive = true;					// �g���Ă邩�ǂ����}�[�N
	float						mLastActiveTime = 0;		// �O��X�V��������
	GameObject*			mGameObject;					// ����GameObject�̑��̃R���|�[�l���g������悤��

	Component();
	virtual ~Component();
};

#endif // !_COMPONENT_H_
