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

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Audio
{
private:
	FMOD::System*							mSystem = nullptr;		// FMODマインシステム
	FMOD::Channel*							mChannel = nullptr;		// FMODチャンネル
	unordered_map<string, FMOD::Sound*>		mSoundsMap;				// サウンドマップ

	HRESULT start();
public:
	Audio();
	~Audio();

	HRESULT createStream(const string mPath, FMOD_MODE mode);		// オーディオをストリームとして読み込み
	HRESULT playAudio(string name);									// プレーサウンド
	void update();													// 更新FMOD
};

#endif // !_AUDIO_H_
