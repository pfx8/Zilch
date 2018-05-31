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

	// ���C�g���x
	ImGui::TextUnformatted(u8"���C�g���x(Max : 20.0)");
	ImGui::DragFloat(u8"Strength", &this->mLightStrength, 0.1f, 1.0f, 20.0f);
	ImGui::Separator();

	// ���C�g����
	ImGui::TextUnformatted(u8"�A���r�G���g");
	ImGui::SliderFloat(u8"Ambient", &this->mLightAmbient, 0.0f, 1.0f);
	ImGui::TextUnformatted(u8"�f�B�t���[�Y");
	ImGui::SliderFloat(u8"Diffuse", &this->mLightDiffuse, 0.0f, 1.0f);
	ImGui::TextUnformatted(u8"�X�y�L�����[");
	ImGui::SliderFloat(u8"Specular", &this->mLightSpecular, 0.0f, 1.0f);
	ImGui::Separator();

	// �R���{�{�b�N�X�̕���ݒ�
	ImGui::PushItemWidth(160);
	ImGui::TextUnformatted(u8"ColorType");
	ImGui::Combo(u8"Type", &this->mCurrentLightType, this->mLight, IM_ARRAYSIZE(this->mLight));
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
	ImGui::Separator();

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
	Transform* trans = this->mGameObject->getComponent<Transform>();
	float* v1[3] = { &trans->mPos.x, &trans->mPos.y, &trans->mPos.z };
	this->mLightPos = trans->mPos;

	switch (this->mLightType)
	{
	case LT_direction:
		ImGui::Separator();
		ImGui::TextUnformatted(u8"���C�g����");
		ImGui::SliderFloat("X", &this->mDirectionLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Y", &this->mDirectionLight.direction.y, -1.0f, 1.0f);
		ImGui::SliderFloat("Z", &this->mDirectionLight.direction.z, -1.0f, 1.0f);

		break;
	case LT_point:
		ImGui::TextUnformatted(u8"�ʒu");
		ImGui::InputFloat3(u8"pos", *v1);
		ImGui::Separator();

		ImGui::TextUnformatted(u8"�|�C���g���C�g�����p�����[�^");
		ImGui::InputFloat("Constant", &this->mPointLight.constant);
		ImGui::InputFloat("Linear", &this->mPointLight.linear);
		ImGui::InputFloat("Quadratic", &this->mPointLight.quadratic);

		break;
	case LT_spot:
		ImGui::TextUnformatted(u8"�ʒu");
		ImGui::InputFloat3(u8"Pos", *v1);;
		ImGui::Separator();

		ImGui::TextUnformatted(u8"���C�g����");
		ImGui::SliderFloat("X", &this->mDirectionLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Y", &this->mDirectionLight.direction.y, -1.0f, 1.0f);
		ImGui::SliderFloat("Z", &this->mDirectionLight.direction.z, -1.0f, 1.0f);
		ImGui::Separator();

		ImGui::TextUnformatted(u8"�X�|�b�g�x�N�g���ƃ��C�g�x�N�g���̃R�T�C��");
		ImGui::SliderFloat("cos", &this->mSpotLight.cutOff, -1.0f, 1.0f);

		break;
	}
}