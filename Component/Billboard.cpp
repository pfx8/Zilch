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
Billboard::Billboard()
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Billboard::~Billboard()
{

}

//*****************************************************************************
//
// ������
//
//*****************************************************************************
void Billboard::start()
{
	// �r���{�[�h�̕ϊ��s����擾
	this->mTrans = this->mGameObject->getComponent<Transform>();
}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void Billboard::update()
{
	// �J��������r���{�[�h�܂ł̕����x�N�g�����v�Z
	D3DXVECTOR3 cameraPos = this->mMainCamera->getComponent<Transform>()->mPos;
	D3DXVECTOR3 cameraDir = cameraPos - this->mTrans->mPos;
	
	// Y���ɂ͊֌W�Ȃ��̂ł�������Y���̐��l���̂ĂāA���K�����ĕ����x�N�g�����ł���
	cameraDir = D3DXVECTOR3(cameraDir.x, 0.0f, cameraDir.z);
	D3DXVec3Normalize(&cameraDir, &cameraDir);

	// �J�����̃r���[�C���O�s����擾
	D3DXMATRIX viewMatrix = mMainCamera->getComponent<Camera>()->mViewMatrix;
	// �r���{�[�h�s������
	D3DXMATRIX billboardMatrix;
	D3DXMatrixIdentity(&billboardMatrix);
	billboardMatrix._11 = viewMatrix._11;
	billboardMatrix._13 = viewMatrix._13;
	billboardMatrix._31 = viewMatrix._31;
	billboardMatrix._33 = viewMatrix._33;

	// �t�s����v�Z
	D3DXMatrixInverse(&billboardMatrix, NULL, &billboardMatrix);

	// �r���{�[�h�̃��[���h�ϊ��s����X�V
	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	this->mTrans->mWorldMatrix = billboardMatrix * temp;
}