//*****************************************************************************
//
// ���ԏ��� [Time.h]
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
	// �Q�[���̎n�܂肩�玞�Ԃ�ۑ���v�Z
	float mCurrentTime;					// ���̎���
	float mDeltaTime;						// �f���^����
	float mLastTime = 0;					// �O�̎���

	Time();
	~Time();

	void update();								// ���Ԃ��X�V
};

#endif // !_TIME_H_
