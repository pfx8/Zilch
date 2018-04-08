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

	this->mFont = nullptr;

	// フロントを初期化
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &this->mFont);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
DebugMessage::~DebugMessage()
{
	RELEASE_POINT(this->mFont);
}

//*****************************************************************************
//
// 描画したい座標メッセージを設定
//
//*****************************************************************************
void DebugMessage::setPosMessage(const string name, D3DXVECTOR3 pos)
{
	mPosMessageMaps.insert({ name, pos });
}

//*****************************************************************************
//
// 座標を描画
//
//*****************************************************************************
void DebugMessage::draw()
{
	// デバッグメッセージの位置
	RECT rectCoor = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	unsigned int fontSize = 18;
	char str[256];

	for (auto it : mPosMessageMaps)
	{
		// 文字列を作る
		sprintf_s(str, _T("<%s> [X:%.2f, Y:%.2f, Z:%.2f]"), it.first.c_str(), it.second.x, it.second.y, it.second.z);

		// 文字列を描画する
		this->mFont->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));

		rectCoor.top += fontSize;
	}
	
}