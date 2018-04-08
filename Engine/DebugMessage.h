//*****************************************************************************
//
// デバックメッセージ処理 [DebugMessage.h]
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
// クラス宣言
//
//*****************************************************************************
class DebugMessage
{
private:
	LPD3DXFONT								mFont;								// フォントのポインタ
	map<string, D3DXVECTOR3> mPosMessageMaps;		// 文字と座標を保存

public:
	DebugMessage();
	~DebugMessage();

	void setPosMessage(const string name, D3DXVECTOR3 pos);		// 描画したい座標メッセージを設定
	void draw();																	// 座標を描画する
};

#endif // !Debug_MESSAGE_H_
