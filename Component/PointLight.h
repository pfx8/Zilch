//*****************************************************************************
//
// �|�C���g���C�g���� [PointLight.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "Component.h"
#include "../Engine/Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class PointLight : public Component
{
private:

public:
	// �|�C���g���C�g��������
	// Luminosity = 1 / Attenuation
	// Attenuation = Constant + Linear * Distance + Quadratic * Distance ^ 2
	// http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation

	// ���x = 1 / �����l
	// �����l = 1.0/(constant + linear * d + quadratic * d^2)
	float				mConstant;			// �萔�A����1.0��
	float				mLinear;			// ���j�A�I�ŋ��x������������
	float				mQuadratic;			// �񎟂ŋ��x������������

	D3DXVECTOR3			mLightPos;			// ���C�g�̈ʒu
	D3DXVECTOR4			mLightColor;		// ���C�g�̃J���[

	PointLight();
	virtual ~PointLight();

	void drawImGui();						// ImGui��PointLight�̃f�[�^���o��
};

#endif // !_PONIT_LIGHT_H_