//*****************************************************************************
//
// �ϊ����� [Transform.cpp]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#include "Transform.h"

#include "Billboard.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Transform::Transform(void)
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Transform::~Transform(void)
{

}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void Transform::update(void)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(&this->mWorldMatrix);
	D3DXMatrixIdentity(&this->mNormalMatrix);

	// �`�F�b�N�r���{�[�h
	//if (this->mParentGameObject->getComponent<Billboard>() != nullptr)
	//{
	//	this->mWorldMatrix = this->mParentGameObject->getComponent<Billboard>()->setBillboard();
	//}

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, mScl.x, mScl.y, mScl.z);
	this->mWorldMatrix *= mtxScl;
	this->mNormalMatrix *= mtxScl;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(mRot.y), D3DXToRadian(mRot.x), D3DXToRadian(mRot.z));
	this->mWorldMatrix *= mtxRot;
	this->mNormalMatrix *= mtxRot;

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, mPos.x, mPos.y, mPos.z);
	this->mWorldMatrix *= mtxTranslate;
}

//*****************************************************************************
//
// ImGui��Transform�̃f�[�^���o��
//
//*****************************************************************************
void Transform::drawImGui(void)
{
	ImGui::Text(u8"�X�P�[��(X,Y,Z)");
	float* v1[3] = { &this->mScl.x, &this->mScl.y, &this->mScl.z };
	ImGui::InputFloat3("Scl", *v1);
	ImGui::Separator();

	ImGui::Text(u8"��]");

	ImGui::PushItemWidth(200);
	ImGui::SliderFloat("X", &this->mRot.x, 0.0f, 360.0f);
	ImGui::SliderFloat("Y", &this->mRot.y, 0.0f, 360.0f);
	ImGui::SliderFloat("Z", &this->mRot.z, 0.0f, 360.0f);
	ImGui::Separator();

	ImGui::Text(u8"�ʒu(X,Y,Z)");
	float* v2[3] = { &this->mPos.x, &this->mPos.y, &this->mPos.z };
	ImGui::InputFloat3("Pos", *v2);
}