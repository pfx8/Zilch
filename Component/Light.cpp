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
	// ���C�g�J���[
	ImGui::ColorEdit4(u8"���C�g�J���[", this->mLightColor);
	ImGui::Separator();

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
		this->mLightType = LT_spot;
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
	float* v1[3] {&this->mLightPos.x, &this->mLightPos.y, &this->mLightPos.z};

	switch (this->mLightType)
	{
	case LT_direction:
		ImGui::Text(u8"���C�g����");
		ImGui::SliderFloat("X", &this->mDirectionLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Y", &this->mDirectionLight.direction.y, -1.0f, 1.0f);
		ImGui::SliderFloat("Z", &this->mDirectionLight.direction.z, -1.0f, 1.0f);

		break;
	case LT_point:
		ImGui::Text(u8"���C�g�ʒu");
		ImGui::InputFloat3("pos", *v1);
		ImGui::Separator();

		ImGui::Text(u8"�|�C���g���C�g�����p�����[�^");
		ImGui::InputFloat("Constant", &this->mPointLight.constant);
		ImGui::InputFloat("Linear", &this->mPointLight.linear);
		ImGui::InputFloat("Quadratic", &this->mPointLight.quadratic);

		break;
	case LT_spot:
		ImGui::Text(u8"���C�g����");
		ImGui::SliderFloat("X", &this->mDirectionLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Y", &this->mDirectionLight.direction.y, -1.0f, 1.0f);
		ImGui::SliderFloat("Z", &this->mDirectionLight.direction.z, -1.0f, 1.0f);
		ImGui::Separator();

		ImGui::Text(u8"�X�|�b�g�x�N�g���ƃ��C�g�x�N�g���̃R�T�C��");
		ImGui::SliderFloat("cos", &this->mSpotLight.cutOff, -1.0f, 1.0f);

		break;
	}
}