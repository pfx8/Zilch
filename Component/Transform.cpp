//*****************************************************************************
//
// �ϊ����� [Transform.cpp]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#include "Transform.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Transform::Transform()
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Transform::~Transform()
{

}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void Transform::update()
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxScl, mtxTranslate;

	// ���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(&this->mWorldMatrix);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, mScl.x, mScl.y, mScl.z);
	//D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &mtxScl);
	this->mWorldMatrix = this->mWorldMatrix * mtxScl;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&this->mRotMatrix, mRot.y, mRot.x, mRot.z);
	//D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &this->mRotMatrix);
	this->mWorldMatrix = this->mWorldMatrix * this->mRotMatrix;

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, mPos.x, mPos.y, mPos.z);
	//D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &mtxTranslate);
	this->mWorldMatrix = this->mWorldMatrix * mtxTranslate;
}

//*****************************************************************************
//
// ImGui��Transform�̃f�[�^���o��
//
//*****************************************************************************
void Transform::drawImGui()
{
	ImGui::Text(u8"�X�P�[��(X,Y,Z)");
	float* v1[3] {&this->mScl.x, &this->mScl.y, &this->mScl.z};
	ImGui::InputFloat3("Scl", *v1);
	ImGui::Separator();

	ImGui::Text(u8"��]");
	ImGui::SliderFloat("X", &this->mRot.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Y", &this->mRot.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Z", &this->mRot.z, -1.0f, 1.0f);
	ImGui::Separator();

	ImGui::Text(u8"�ʒu(X,Y,Z)");
	float* v2[3] {&this->mPos.x, &this->mPos.y, &this->mPos.z};
	ImGui::InputFloat3("Tran", *v2);
}