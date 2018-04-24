//*****************************************************************************
//
// ���C�g���� [Light.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Component.h"
#include "../Engine/Engine.h"

class Light : public Component
{
private:

public:
	D3DXVECTOR3			mPosition;				// ���z�̈ʒu
	D3DXVECTOR3			mLightDirection;		// ���C�g�̕���
	D3DXVECTOR4			mLightColor;			// ���C�g�̃J���[



	Light();
	virtual ~Light();
};

#endif // !_LIGHT_H_
