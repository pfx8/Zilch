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
Audio::Audio(void)
{
	
}

//*****************************************************************************
//
// オーディオシステムを初期化
//
//*****************************************************************************
HRESULT Audio::start(void)
{
	FMOD_RESULT result;

	// FMODシステムを初期化
	result = FMOD::System_Create(&this->mSystem);
	if (result != FMOD_OK)
	{
		// Debugウインドへ
		cout << "<Error> FMOD::System_Create ... failed!" << endl << FMOD_ErrorString(result);
		return E_FAIL;
	}

	// FMODを初期化
	result = this->mSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		// Debugウインドへ
		cout << "<Error> FMOD init ... fail!ed" << endl << FMOD_ErrorString(result);
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Audio::~Audio(void)
{
	this->mSystem->release();
	this->mSounds.clear();
}

//*****************************************************************************
//
// オーディオをストリームとして読み込み
//
//*****************************************************************************
HRESULT Audio::createStream(const string path, FMOD_MODE mode)
{
	FMOD_RESULT result;

	// サウンドを読み込み
	FMOD::Sound* sound;
	result = this->mSystem->createStream(path.c_str(), mode, 0, &sound);
	if (result != FMOD_OK)
	{
		// Debugウインドへ
		cout << "<Error> FMOD system create stream ... " << FMOD_ErrorString(result);
		return E_FAIL;
	}

	string fileName = path.substr(path.find_last_of("//") + 1, path.find_first_of("."));

	// サウンドマップに入れる
	this->mSounds.insert(make_pair(fileName, sound));

	return S_OK;
}

//*****************************************************************************
//
// プレーサウンド
//
//*****************************************************************************
HRESULT Audio::playAudio(string name)
{
	FMOD_RESULT result;

	// 名前からサウンドを取得
	FMOD::Sound* sound;
	if (this->mSounds.find(name) != this->mSounds.end())
	{
		sound = this->mSounds[name];
	}
	else
	{
		return E_FAIL;
	}

	// プレーサウンド
	//result = PlaySound(sound, )
}

//*****************************************************************************
//
// 更新FMOD
//
//*****************************************************************************
void Audio::update(void)
{

}