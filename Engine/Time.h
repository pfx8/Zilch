//*****************************************************************************
//
// 時間処理 [Time.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _TIME_H_
#define _TIME_H_

#include "Engine.h"

class Time
{
private:

public:
	// ゲームの始まりから時間を保存や計算
	float mCurrentTime;					// 今の時間
	float mDeltaTime;						// デルタ時間
	float mLastTime = 0;					// 前の時間

	Time();
	~Time();

	void update();								// 時間を更新
};

#endif // !_TIME_H_
