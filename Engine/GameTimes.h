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

class GameTimes
{
private:

public:
	// �Q�[���̎n�܂肩�玞�Ԃ�ۑ���v�Z
	float mCurrentTime;					// ���̎���
	float mDeltaTime;						// �f���^����
	float mLastTime = 0;					// �O�̎���

	GameTimes();
	~GameTimes();

	void update();								// ���Ԃ��X�V
};

#endif // !_GAME_TIMES_H_
