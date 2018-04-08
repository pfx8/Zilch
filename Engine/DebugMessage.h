//*****************************************************************************
//
// �f�o�b�N���b�Z�[�W���� [DebugMessage.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _DEBUG_MESSAGE_H_
#define _DEBUG_MESSAGE_H_

#include <map>

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class DebugMessage
{
private:
	LPD3DXFONT								mFont;								// �t�H���g�̃|�C���^
	map<string, D3DXVECTOR3> mPosMessageMaps;		// �����ƍ��W��ۑ�

public:
	DebugMessage();
	~DebugMessage();

	void setPosMessage(const string name, D3DXVECTOR3 pos);		// �`�悵�������W���b�Z�[�W��ݒ�
	void draw();																	// ���W��`�悷��
};

#endif // !Debug_MESSAGE_H_
