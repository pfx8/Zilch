//*****************************************************************************
//
// オーディオ処理 [Audio.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Audio.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Audio::Audio()
{
	
}

//*****************************************************************************
//
// オーディオシステムを初期化
//
//*****************************************************************************
HRESULT Audio::start()
{
	// システムを初期化、また初期化の結果をmResultに保存
	this->mResult = FMOD::System_Create(&this->mSystem);
	if (this->mResult != FMOD_OK)
	{
		cout << "[Error] FMOD::System_Create ... " << FMOD_ErrorString(this->mResult);
		return E_FAIL;
	}

	// FMODを初期化
	this->mResult = this->mSystem->init(16, FMOD_INIT_NORMAL, 0);
	if (this->mResult != FMOD_OK)
	{
		cout << "[Error] FMOD init ... " << FMOD_ErrorString(this->mResult);
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Audio::~Audio()
{

}

//*****************************************************************************
//
// オーディオをストリームとして読み込み
//
//*****************************************************************************
HRESULT Audio::createStream(const string name, const string path, FMOD_MODE mode)
{
	FMOD::Sound* sound = new FMOD::Sound();
	this->mSounds.insert(make_pair(name, sound));
	this->mResult = this->mSystem->createStream(path.c_str(), mode, 0, &sound);
	if (this->mResult != FMOD_OK)
	{
		cout << "[Error] FMOD system create stream ... " << FMOD_ErrorString(this->mResult);
		return E_FAIL;
	}
}