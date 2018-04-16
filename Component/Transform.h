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
#include "../Engine/Engine.h"

class Transform : public Component
{
private:
	void update();

public:
	D3DXMATRIX			worldMatrix;			// ���[���h�ϊ��s��

	D3DXVECTOR3		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	D3DXVECTOR3		scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				// �g��k��
	D3DXVECTOR3		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �p�x

	Transform();
	virtual ~Transform();

};

#endif // !_TRANSFORM_H_
