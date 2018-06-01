//*****************************************************************************
//
// �R���|�[�l���g�x�[�X�N���X [Component.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "..\Engine\Engine.h"

#include "..\GameObject\GameObject.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Component
{
	friend class GameObject;

private:

public:
	GameObject*			mParentGameObject;			// ������GameObject�|�C���^
	bool				mIsStart = false;			// �X�^�[�g�}�b�N

	Component(void);
	virtual ~Component(void);

	virtual void start(void) {};
	virtual void update(void) {};
	virtual void drawImGui(void) {};
};

#endif // !_COMPONENT_H_
