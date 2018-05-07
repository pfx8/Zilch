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

//*****************************************************************************
//
// �e���C�g�\����
//
//*****************************************************************************
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

//*****************************************************************************
//
// �񋓑�
//
//*****************************************************************************
enum LightType
{
	LT_point,
	LT_direction,
	LT_flash,
};


//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Light : public Component
{
private:
	int					mCurrentLightType;

	void start();		// ������

public:
	LightType			mLightType;			// ���C�g�^�C�v
	D3DXVECTOR3			mLightPos;			// ���C�g�̈ʒu
	D3DXVECTOR4			mLightColor;		// ���C�g�̃J���[

	PointLight			mPointLight;		// �|�C���g���C�g

	Light();
	virtual ~Light();

	void drawImGui();						// ImGui��PointLight�̃f�[�^���o��
};

#endif // !_LIGHT_H_