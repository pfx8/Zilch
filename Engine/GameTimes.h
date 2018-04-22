//*****************************************************************************
//
// ゲームタイム処理 [GameTimes.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _GAME_TIMES_H_
#define _GAME_TIMES_H_

#include "Engine.h"

class GameTimes
{
private:

public:
	// ゲームの始まりから時間を保存や計算
	float mCurrentTime = 0.0f;				// 今の時間
	float mDeltaTime = 0.0f;					// デルタ時間
	float mLastTime = 0.0F;					// 前の時間

	GameTimes();
	~GameTimes();

	void update();								// 時間を更新
};

#endif // !_GAME_TIMES_H_
