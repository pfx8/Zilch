//*****************************************************************************
//
// �������C�g���� [DirectionalLight.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "Component.h"
#include "../Engine/Engine.h"

class DirectionalLight : public Component
{
private:

public:
	D3DXVECTOR3			mSunPos;				// ���z�̈ʒu
	D3DXVECTOR3			mLightDirection;		// ���C�g�̕���
	D3DXVECTOR4			mLightColor;			// ���C�g�̃J���[

	DirectionalLight();
	virtual ~DirectionalLight();
};

#endif // !_DIRECTIONAL_LIGHT_H_
