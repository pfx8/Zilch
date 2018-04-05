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

//--------FMOD--------//
#include <fmod.hpp>
#include <fmod_errors.h>

class Audio
{
private:
	FMOD_RESULT mResult;
	FMOD::System* mSystem;		// fmod.hpp���K�v
	HRESULT start();

	unordered_map<string, FMOD::Sound> mSounds;		// ���ׂẴI�[�f�B�I�������ɕۑ�
public:
	Audio();
	~Audio();

	HRESULT createStream(const string name, const string mPath, FMOD_MODE mode);		// �I�[�f�B�I���X�g���[���Ƃ��ēǂݍ���

};

#endif // !_AUDIO_H_
