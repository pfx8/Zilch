//*****************************************************************************
//
// �L�����N�^�[�x�[�X���� [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Engine\Engine.h"
#include "Engine\DebugMessage.h"
#include "Model\Model.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Character
{
private:
	DebugMessage*	message;		// Debug���b�Z�[�W

public:
	Model*			model = nullptr;			// ���f��

	Character();
	~Character();

	void InitCharacter();				// ������
	void OutputMessage(int row);		// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	virtual void Update();				// �L�����N�^�[�X�V
};
#endif // !_CHARACTER_H_

