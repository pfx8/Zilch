//*****************************************************************************
//
// �Q�[���^�C������ [GameTimes.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _GAME_TIMES_H_
#define _GAME_TIMES_H_

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class GameTimes
{
private:

public:
	float mCurrentTime = 0.0f;			// ���̎���(�~���b)
	float mDeltaTime = 0.0f;			// �f���^����(�~���b)
	float mLastTime = 0.0f;				// �O�̎���(�~���b)

	GameTimes();
	~GameTimes();

	void update();					// ���Ԃ��X�V
};

#endif // !_GAME_TIMES_H_
