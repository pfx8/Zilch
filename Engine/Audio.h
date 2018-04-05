//*****************************************************************************
//
// オーディオ処理 [Audio.h]
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
	FMOD::System* mSystem;		// fmod.hppが必要
	HRESULT start();

	unordered_map<string, FMOD::Sound> mSounds;		// すべてのオーディオをここに保存
public:
	Audio();
	~Audio();

	HRESULT createStream(const string name, const string mPath, FMOD_MODE mode);		// オーディオをストリームとして読み込み

};

#endif // !_AUDIO_H_
