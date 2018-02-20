//*****************************************************************************
//
// �L�����N�^�[�x�[�X���� [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <map>

#include "Model.h"
#include "Sound.h"
#include "..\Engine.h"
#include "..\DebugMessage.h"
#include "..\Shader\CelShader.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Character
{
private:

public:
	DebugMessage*	message;		// Debug���b�Z�[�W

	Character();
	~Character();

	D3DXVECTOR3  MoveAlongVecLook(float speedCoefficient);	// ���������ɉ����Ĉړ�
	void PosToMessageAndMessageDraw(int row);	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void SetWorldMatrix();						// ���[���h�ϊ���
	void RotationVecUp(float angle);			// ������̃x�N�g���ɂ��ĉ�]

	virtual void Update(float rot);						// �L�����N�^�[�X�V
	virtual void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);	// �L�����N�^�[�̕`��

	void InitCharacter();

	void Move();								// �L�����N�^�[�ړ�
};
#endif // !_CHARACTER_H_

