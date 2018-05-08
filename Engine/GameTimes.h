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

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class GameTimes
{
private:

public:
	float mCurrentTime = 0.0f;			// 今の時間(ミリ秒)
	float mDeltaTime = 0.0f;			// デルタ時間(ミリ秒)
	float mLastTime = 0.0f;				// 前の時間(ミリ秒)

	GameTimes();
	~GameTimes();

	void update();					// 時間を更新
};

#endif // !_GAME_TIMES_H_
