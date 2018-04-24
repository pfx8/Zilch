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

struct PointLight
{
	// �|�C���g���C�g��������
	// Luminosity = 1 / Attenuation
	// Attenuation = Constant + Linear * Distance + Quadratic * Distance ^ 2
	// http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation

	// ���x = 1 / �����l
	// �����l = 1.0/(constant + linear * d + quadratic * d^2)
	float				constant;			// �萔�A����1.0��
	float				linear;				// ���j�A�I�ŋ��x������������
	float				quadratic;			// �񎟂ŋ��x������������
};

class Light : public Component
{
private:

public:
	D3DXVECTOR3			mLightPos;				// ���z�̈ʒu
	//D3DXVECTOR3			mLightDirection;		// ���C�g�̕���
	D3DXVECTOR4			mLightColor;			// ���C�g�̃J���[
	PointLight			mPointLight;			// �|�C���g���C�g�̃v���p�e�B

	Light();
	virtual ~Light();
};

#endif // !_LIGHT_H_
