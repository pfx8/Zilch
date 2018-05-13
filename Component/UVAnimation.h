//*****************************************************************************
//
// �e�N�X�`���A�j���[�V�������� [UVAnimation.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _UVANIMATION_H_
#define _UVANIMATION_H_

#include "Component.h"

#include "Engine\Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class UVAnimation : public Component
{
private:
	void start();

public:
	D3DXVECTOR2		mSize;		// �e�N�X�`���̃T�C�Y
	float			mTime;		// �A�j���[�V�����̎���

	UVAnimation(D3DXVECTOR2 size, float time);
	~UVAnimation();
};

#endif // !_UVANIMATION_H_
