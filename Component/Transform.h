//*****************************************************************************
//
// �ϊ����� [Transform.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"

#include "..\Engine\Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Transform : public Component
{
private:
	void update();

public:
	D3DXMATRIX		mWorldMatrix;			// ���[���h�ϊ��s��
	D3DXMATRIX		mNormalMatrix;			// �@���v�Z�p�s��A��]*�X�P�[��

	D3DXVECTOR3		mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	D3DXVECTOR3		mScl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			// �g��k��
	D3DXVECTOR3		mRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �p�x

	Transform();
	virtual ~Transform();

	void drawImGui();						// ImGui��Transform�̃f�[�^���o��
};

#endif // !_TRANSFORM_H_
