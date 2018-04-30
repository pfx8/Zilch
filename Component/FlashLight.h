//*****************************************************************************
//
// �t���b�V�����C�g���� [FlashLight.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _FLASH_LIGHT_H_
#define _FLASH_LIGHT_H_

#include "Component.h"
#include "../Engine/Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class FlashLight : public Component
{
private:

public:
	D3DXVECTOR3			mLightPos;				// ���z�̈ʒu
	D3DXVECTOR3			mLightDirection;		// ���C�g�̕���
	D3DXVECTOR4			mLightColor;			// ���C�g�̃J���[
	float				mCutOff;				// ���C�g�p�x�͈̔�(Radian�Ōv�Z)

	FlashLight();
	virtual ~FlashLight();
};

#endif // !_LIGHT_H_
