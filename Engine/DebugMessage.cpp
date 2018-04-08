//*****************************************************************************
//
// デバックメッセージ処理 [DebugMessage.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "DebugMessage.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
DebugMessage::DebugMessage()
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	this->font = nullptr;
	this->rectCoor = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// フロントを初期化
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &this->font);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
DebugMessage::~DebugMessage()
{
	RELEASE_POINT(this->font);
}

//*****************************************************************************
//
// 座標を描画
//
//*****************************************************************************
void DebugMessage::DrawPosMessage(const char name[], D3DXVECTOR3 OutputPos, D3DXVECTOR2 MessagePos)
{
	RECT rectCoor = { int(MessagePos.x), int(MessagePos.y), SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	// 文字列を作る
	sprintf(str, _T("%s X:%.2f,Y:%.2f,Z:%.2f"), name, OutputPos.x, OutputPos.y, OutputPos.z);

	// 文字列を描画する
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}

//*****************************************************************************
//
// 行列を描画
//
//*****************************************************************************
void DebugMessage::DrawMatrixMessage(D3DXMATRIX* matrix, D3DXVECTOR2 MessagePos)
{
	D3DXMATRIX* mat = matrix;

	RECT rectCoor = { int(MessagePos.x), int(MessagePos.y), SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	// 文字列を作る
	sprintf(str, _T("%.2f,%.2f,%.2f,%.2f"), mat->_11, mat->_12, mat->_13, mat->_14);
	// 文字列を描画する
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
	
	rectCoor.top += 18;
	// 文字列を作る
	sprintf(str, _T("%.2f,%.2f,%.2f,%.2f"), mat->_21, mat->_22, mat->_23, mat->_24);
	// 文字列を描画する
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));

	rectCoor.top += 18;
	// 文字列を作る
	sprintf(str, _T("%.2f,%.2f,%.2f,%.2f"), mat->_31, mat->_32, mat->_33, mat->_34);
	// 文字列を描画する
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));

	rectCoor.top += 18;
	// 文字列を作る
	sprintf(str, _T("%.2f,%.2f,%.2f,%.2f"), mat->_41, mat->_42, mat->_43, mat->_44);
	// 文字列を描画する
	this->font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}

//*****************************************************************************
//
// デバッグメッセージ
//
//*****************************************************************************
void DebugMessage::DrawMessage(const char message[])
{
	this->font->DrawText(NULL, &message[0], -1, &this->rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 255, 0xff));	// 文字列を描画する
}