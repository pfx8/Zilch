//*****************************************************************************
//
// �A�j���[�V�����`�����l������ [AnimationChannel.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _ANIMATION_CHANNEL_H_
#define _ANIMATION_CHANNEL_H_

#include "../Engine.h"

//*****************************************************************************
//
// �\���̒�`
//
//*****************************************************************************
struct VertexKey
{
	float								time;			// ���̃t���[��
	D3DXVECTOR3				value;			// ���̃t���[���̒��_���W
};

struct QuaternionKey
{
	float								time;			// ���̃t���[��
	D3DXQUATERNION		value;			// ��]�����l�����ɓ����
};
//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class AnimationChannel
{
private:
	float									mDuration;											// �A�j���[�V�����̑�������(�P�ʂ�fps)
	float									mTicksPerSecond;								// fps/seconds
	unsigned int						mNumChannels;								// �q���m�[�h�̃A�j���[�V������

public:
	vector<VertexKey>			mPosKeys;											// ���_���W
	vector<QuaternionKey>	mRotkeys;											// ��]�l����
	vector<VertexKey>			mSclKeys;											// �g��k���f�[�^

	AnimationChannel();
	~AnimationChannel();
};

#endif // !_ANIMATION_CHANNEL_H_

