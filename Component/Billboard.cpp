//*****************************************************************************
//
// �r���{�[�h���� [Billboard.cpp]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#include "Billboard.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Billboard::Billboard(void)
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Billboard::~Billboard(void)
{

}

//*****************************************************************************
//
// ������
//
//*****************************************************************************
void Billboard::start(void)
{
	// �ʒu����GameObject����擾
	this->mTrans = this->mParentGameObject->getComponent<Transform>();
}

//*****************************************************************************
//
// �r���{�[�h�s��𐶐�
//
//*****************************************************************************
D3DXMATRIX Billboard::setBillboard(void)
{
	D3DXMATRIX viewMatrix = this->mSceneCurrentCamera->mViewMatrix;

	// �r���{�[�h�s������
	D3DXMatrixIdentity(&this->mBillboardMatrix);

	this->mBillboardMatrix._11 = viewMatrix._11;
	this->mBillboardMatrix._13 = viewMatrix._13;
	this->mBillboardMatrix._31 = viewMatrix._31;
	this->mBillboardMatrix._33 = viewMatrix._33;

	// �t�s����v�Z
	D3DXMatrixInverse(&this->mBillboardMatrix, NULL, &this->mBillboardMatrix);

	// �r���{�[�h�̃��[���h�ϊ��s����X�V
	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	temp = this->mBillboardMatrix * temp;

	return temp;
}

//*****************************************************************************
//
// GUI�p�l��
//
//*****************************************************************************
void Billboard::drawImGui(void)
{
	ImGui::Text(u8"���[���h�ϊ��s��");
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mTrans->mWorldMatrix._11, this->mTrans->mWorldMatrix._12, this->mTrans->mWorldMatrix._13, this->mTrans->mWorldMatrix._14);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mTrans->mWorldMatrix._21, this->mTrans->mWorldMatrix._22, this->mTrans->mWorldMatrix._23, this->mTrans->mWorldMatrix._24);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mTrans->mWorldMatrix._31, this->mTrans->mWorldMatrix._32, this->mTrans->mWorldMatrix._33, this->mTrans->mWorldMatrix._34);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mTrans->mWorldMatrix._41, this->mTrans->mWorldMatrix._42, this->mTrans->mWorldMatrix._43, this->mTrans->mWorldMatrix._44);
	ImGui::Separator();

	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mBillboardMatrix._11, this->mBillboardMatrix._12, this->mBillboardMatrix._13, this->mBillboardMatrix._14);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mBillboardMatrix._21, this->mBillboardMatrix._22, this->mBillboardMatrix._23, this->mBillboardMatrix._24);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mBillboardMatrix._31, this->mBillboardMatrix._32, this->mBillboardMatrix._33, this->mBillboardMatrix._34);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mBillboardMatrix._41, this->mBillboardMatrix._42, this->mBillboardMatrix._43, this->mBillboardMatrix._44);

}