//*****************************************************************************
//
// �A�j���[�V�����`�����l������ [AnimationChannel.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _ANIMATION_CHANNEL_H_
#define _ANIMATION_CHANNEL_H_

#include "..\Engine.h"

//*****************************************************************************
//
// �\���̒�`
//
//*****************************************************************************
struct VertexKey
{
	float				time;			// ���̃t���[��
	D3DXVECTOR3			value;			// ���̃t���[���̒��_���W
};

struct QuaternionKey
{
	float				time;			// ���̃t���[��
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

public:
	wstring						mNodeName;				// �m�[�h���O
	vector<VertexKey>			mPosKeys;				// ���_���W
	vector<QuaternionKey>		mRotkeys;				// ��]�l����
	vector<VertexKey>			mSclKeys;				// �g��k���f�[�^

	AnimationChannel(void);
	~AnimationChannel(void);
};

#endif // !_ANIMATION_CHANNEL_H_

