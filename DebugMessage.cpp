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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	m_Font = NULL;
	m_rectCoor = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// フロントを初期化
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_Font);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
DebugMessage::~DebugMessage()
{
	RELEASE_POINT(m_Font);
}

//*****************************************************************************
//
// 文字を描画する
//
//*****************************************************************************
void DebugMessage::DrawPosMessage(const char name[], D3DXVECTOR3 OutputPos, D3DXVECTOR2 MessagePos)
{
	RECT rectCoor = { int(MessagePos.x), int(MessagePos.y), SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	// 文字列を作る
	sprintf(str, _T("%s X:%.2f,Y:%.2f,Z:%.2f"), name, OutputPos.x, OutputPos.y, OutputPos.z);

	// 文字列を描画する
	m_Font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));

}

//*****************************************************************************
//
// デバッグメッセージ
//
//*****************************************************************************
void DebugMessage::DrawMessage(const char message[])
{
	m_Font->DrawText(NULL, &message[0], -1, &m_rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 255, 0xff));	// 文字列を描画する
	//m_rectCoor.top += 18;	// 次の文字列の位置を更新
}