//*****************************************************************************
//
// �f�o�b�N���b�Z�[�W���� [DebugMessage.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "DebugMessage.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
DebugMessage::DebugMessage()
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	this->mFont = nullptr;

	// �t�����g��������
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &this->mFont);
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
DebugMessage::~DebugMessage()
{
	RELEASE_POINT(this->mFont);
}

//*****************************************************************************
//
// �`�悵�������W���b�Z�[�W��ݒ�
//
//*****************************************************************************
void DebugMessage::setPosMessage(const string name, D3DXVECTOR3 pos)
{
	mPosMessageMaps.insert({ name, pos });
}

//*****************************************************************************
//
// ���W��`��
//
//*****************************************************************************
void DebugMessage::draw()
{
	// �f�o�b�O���b�Z�[�W�̈ʒu
	RECT rectCoor = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	unsigned int fontSize = 18;
	char str[256];

	for (auto it : mPosMessageMaps)
	{
		// ����������
		sprintf_s(str, _T("<%s> [X:%.2f, Y:%.2f, Z:%.2f]"), it.first.c_str(), it.second.x, it.second.y, it.second.z);

		// �������`�悷��
		this->mFont->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));

		rectCoor.top += fontSize;
	}
	
}