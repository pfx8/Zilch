//*****************************************************************************
//
// ���C�g���� [Light.cpp]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#include "Light.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Light::Light()
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Light::~Light()
{

}

//*****************************************************************************
//
// ������
//
//*****************************************************************************
void Light::start()
{
	this->mCurrentLightType = this->mLightType;
}

//*****************************************************************************
//
// ImGui��PointLight�̃f�[�^���o��
//
//*****************************************************************************
void Light::drawImGui()
{
	// �R���{�{�b�N�X�̕���ݒ�
	ImGui::PushItemWidth(160);
	ImGui::Text(u8"���C�g�^�C�v");
	ImGui::Combo(" ", &this->mCurrentLightType, this->mLight, IM_ARRAYSIZE(this->mLight));
	switch (this->mCurrentLightType)
	{
	case 0:
		this->mLightType = LT_direction;
		break;
	case 1:
		this->mLightType = LT_point;
		break;
	case 2:
		this->mLightType = LT_flash;
		break;
	}

	// ��ނɂ���ă��C�g�̒���ImGui��`��
	lightControllerImGui();
}

//*****************************************************************************
//
// �e���C�g�̒���ImGui
//
//*****************************************************************************
void Light::lightControllerImGui()
{
	// ���C�g�ʒu���͔z��
	float* v1[3] = { &this->mLightPos.x, &this->mLightPos.y, &this->mLightPos.z };

	switch (this->mLightType)
	{
	case LT_direction:
		break;
	case LT_point:
		ImGui::Text(u8"���C�g�ʒu");
		ImGui::InputFloat3("pos", *v1);
		ImGui::Separator();

		ImGui::Text(u8"�|�C���g���C�g�����p�����[�^");
		ImGui::InputFloat("Constant", &this->mPointLight.constant);
		ImGui::InputFloat("Linear", &this->mPointLight.linear);
		ImGui::InputFloat("Quadratic", &this->mPointLight.quadratic);
		ImGui::Separator();
		break;
	case LT_flash:
		break;
	}
}