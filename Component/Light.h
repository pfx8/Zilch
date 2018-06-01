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
#include "Transform.h"

#include "..\Engine\Engine.h"

//*****************************************************************************
//
// �e���C�g�\����
//
//*****************************************************************************
struct DirectionLight
{
	D3DXVECTOR3			direction;
};

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

struct SpotLight
{
	D3DXVECTOR3			direction;			// ���C�g�̕���
	float				cutOff;				// �X�|�b�g�x�N�g���ƃ��C�g�x�N�g���̃R�T�C���l
	bool				isSmooth;			// �X���[�X�`�F�b�N
};

//*****************************************************************************
//
// �񋓑�
//
//*****************************************************************************
enum LightType
{
	LT_direction,
	LT_point,
	LT_spot,
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
	const char*			mLight[3] = { u8"�w�������C�g", u8"�|�C���g���C�g", u8"�X�|�b�g���C�g" };

public:
	D3DXVECTOR3			mLightPos;
	D3DXVECTOR4			mLightColor;
	float				mLightStrength = 1.0f;
	float				mLightAmbient = 0.2f;
	float				mLightDiffuse = 0.5f;
	float				mLightSpecular = 1.0f;

	LightType			mLightType;
	PointLight			mPointLight;
	DirectionLight		mDirectionLight;
	SpotLight			mSpotLight;

	Light(void);
	~Light(void);

	void start(void);
	void drawImGui(void);
	void lightControllerImGui(void);
};

#endif // !_LIGHT_H_