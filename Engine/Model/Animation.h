//*****************************************************************************
//
// �A�j���[�V�������� [Animation.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "AnimationChannel.h"
#include "../Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Animation
{
	friend class Mesh;
private:
	string							mName;														// �A�j���[�V�����̖��O
	float							mDuration;													// �A�j���[�V�����̑�������(�P�ʂ�fps)
	float							mTicksPerSecond;										// fps/seconds
	unsigned int				mNumChannels;										// �q���m�[�h�̃A�j���[�V������

	void processNode(aiNode *node, const aiScene *scene);			// �m�[�h����
	HRESULT loadAnimation(string const &path);							// �A�j���[�V������ǂݍ���

public:

	Animation(string const &path);
	~Animation();
};

#endif // !_ANIMATION_H_

