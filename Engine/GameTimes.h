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
	DWORD mCurrentTime = 0.0;
	float mDeltaTime = 0.0f;
	DWORD mLastUpdateTime = 0.0;

	GameTimes(void);
	~GameTimes(void);

	void update(void);
};

#endif // !_GAME_TIMES_H_
