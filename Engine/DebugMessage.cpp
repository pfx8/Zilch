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

	this->font = nullptr;
	this->rectCoor = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �t�����g��������
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &this->font);
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
DebugMessage::~DebugMessage()
{
	RELEASE_POINT(this->font);
}

//*****************************************************************************
//
// ���W��`��
//
//*****************************************************************************
void DebugMessage::DrawPosMessage(const char name[], D3DXVECTOR3 OutputPos, D3DXVECTOR2 MessagePos)
{
	RECT rectCoor = { int(MessagePos.x), int(MessagePos.y), SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	// ����������
	sprintf(str, _T("%s X:%.2f,Y:%.2f,Z:%.2f"), name, OutputPos.x, OutputPos.y, OutputPos.z);

	// �������`�悷��
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}

//*****************************************************************************
//
// �s���`��
//
//*****************************************************************************
void DebugMessage::DrawMatrixMessage(D3DXMATRIX* matrix, D3DXVECTOR2 MessagePos)
{
	D3DXMATRIX* mat = matrix;

	RECT rectCoor = { int(MessagePos.x), int(MessagePos.y), SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	// ����������
	sprintf(str, _T("%.2f,%.2f,%.2f,%.2f"), mat->_11, mat->_12, mat->_13, mat->_14);
	// �������`�悷��
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
	
	rectCoor.top += 18;
	// ����������
	sprintf(str, _T("%.2f,%.2f,%.2f,%.2f"), mat->_21, mat->_22, mat->_23, mat->_24);
	// �������`�悷��
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));

	rectCoor.top += 18;
	// ����������
	sprintf(str, _T("%.2f,%.2f,%.2f,%.2f"), mat->_31, mat->_32, mat->_33, mat->_34);
	// �������`�悷��
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));

	rectCoor.top += 18;
	// ����������
	sprintf(str, _T("%.2f,%.2f,%.2f,%.2f"), mat->_41, mat->_42, mat->_43, mat->_44);
	// �������`�悷��
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}

//*****************************************************************************
//
// �f�o�b�O���b�Z�[�W
//
//*****************************************************************************
void DebugMessage::DrawMessage(const char message[])
{
	this->font->DrawText(NULL, &message[0], -1, &this->rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 255, 0xff));	// �������`�悷��
}