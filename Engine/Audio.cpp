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
	// 結果変数
	FMOD_RESULT result;

	// FMODシステムを初期化
	result = FMOD::System_Create(&this->mSystem);
	if (result != FMOD_OK)
	{
		cout << "[Error] FMOD::System_Create ... fail!" << endl << FMOD_ErrorString(result);
		return E_FAIL;
	}

	// FMODを初期化
	result = this->mSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		cout << "[Error] FMOD init ... fail!" << endl << FMOD_ErrorString(result);
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
HRESULT Audio::createStream(const string path, FMOD_MODE mode)
{
	FMOD_RESULT result;

	// サウンドを読み込み
	FMOD::Sound* sound;
	result = this->mSystem->createStream(path.c_str(), mode, 0, &sound);
	if (result != FMOD_OK)
	{
		cout << "[Error] FMOD system create stream ... " << FMOD_ErrorString(result);
		return E_FAIL;
	}

	string fileName {path.substr(path.find_last_of("//") + 1, path.find_first_of("."))};
	// サウンドマップに入れる
	this->mSoundsMap.insert(make_pair(fileName, sound));

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
	if (this->mSoundsMap.find(name) != this->mSoundsMap.end())
	{
		sound = this->mSoundsMap[name];
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
void Audio::update()
{

}