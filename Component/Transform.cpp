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
	D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&this->mRotMatrix, mRot.y, mRot.x, mRot.z);
	D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &this->mRotMatrix);

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, mPos.x, mPos.y, mPos.z);
	D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &mtxTranslate);
}
