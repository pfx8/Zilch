//*****************************************************************************
//
// �r���{�[�h���� [Billboard.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "Component.h"
#include "Transform.h"
#include "../Engine/Engine.h"

class Billboard : public Component
{
private:
	Transform			mTrans;				// �r���{�[�h���
	Transform*			mCameraTrans;		// �J�������

	void start() {};
	void update() {};

public:
	GameObject*			mGameObject;					// ����GameObject�̑��̃R���|�[�l���g������悤��
	bool					mStart = false;				// �X�^�[�g�}�b�N

	Billboard();
	virtual ~Billboard();
};

#endif // !_BILLBOARD_H_
