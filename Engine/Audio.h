//*****************************************************************************
//
// �I�[�f�B�I���� [Audio.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Audio
{
private:
	FMOD::System*							mSystem = nullptr;		// FMOD�}�C���V�X�e��
	//FMOD::Channel*							mChannel = nullptr;		// FMOD�`�����l��
	unordered_map<string, FMOD::Sound*>		mSounds;

	HRESULT start(void);
public:
	Audio(void);
	~Audio(void);

	HRESULT createStream(const string mPath, FMOD_MODE mode);		// �I�[�f�B�I���X�g���[���Ƃ��ēǂݍ���
	HRESULT playAudio(string name);									// �v���[�T�E���h
	void update(void);												// �X�VFMOD
};

#endif // !_AUDIO_H_
