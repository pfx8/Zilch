//*****************************************************************************
//
// �f�o�b�N���b�Z�[�W���� [DebugMessage.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _DEBUG_MESSAGE_H_
#define _DEBUG_MESSAGE_H_

#include "Engine.h"

#include <iostream>

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class DebugMessage
{
private:
	LPD3DXFONT			m_Font;	// �t�H���g�̃|�C���^
	RECT					m_rectCoor; // �f�o�b�O���b�Z�[�W�̈ʒu

public:
	DebugMessage();
	~DebugMessage();

	void DrawPosMessage(const char name[], D3DXVECTOR3 OutputPos, D3DXVECTOR2 MessagePos);
	void DrawMessage(const char message[]);	// �f�o�b�O���b�Z�[�W
};

#endif // !Debug_MESSAGE_H_
