//*****************************************************************************
//
// デバックメッセージ処理 [DebugMessage.h]
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
// クラス宣言
//
//*****************************************************************************
class DebugMessage
{
private:
	LPD3DXFONT			m_Font;	// フォントのポインタ
	RECT					m_rectCoor; // デバッグメッセージの位置

public:
	DebugMessage();
	~DebugMessage();

	void DrawPosMessage(const char name[], D3DXVECTOR3 OutputPos, D3DXVECTOR2 MessagePos);
	void DrawMessage(const char message[]);	// デバッグメッセージ
};

#endif // !Debug_MESSAGE_H_
