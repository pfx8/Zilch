//*****************************************************************************
//
// キャラクターベース処理 [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <map>

#include "Engine.h"
#include "DebugMessage.h"
#include "Modules\Model.h"
#include "Modules\Sound.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Character
{
private:
	DebugMessage*	message;		// Debugメッセージ

public:
	Model*			model;			// モデル

	Character();
	~Character();

	void InitCharacter();					//　初期化
	void OutputMessage(int row);			// 座標をメッセージに渡して、画面に描画する
	virtual void Update();				// キャラクター更新
};
#endif // !_CHARACTER_H_

