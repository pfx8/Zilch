//*****************************************************************************
//
// �I�[�f�B�I���� [Audio.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Audio.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Audio::Audio()
{
	
}

//*****************************************************************************
//
// �I�[�f�B�I�V�X�e����������
//
//*****************************************************************************
HRESULT Audio::start()
{
	// �V�X�e�����������A�܂��������̌��ʂ�mResult�ɕۑ�
	this->mResult = FMOD::System_Create(&this->mSystem);
	if (this->mResult != FMOD_OK)
	{
		cout << "[Error] FMOD::System_Create ... " << FMOD_ErrorString(this->mResult);
		return E_FAIL;
	}

	// FMOD��������
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
// �f�X�g���N�^
//
//*****************************************************************************
Audio::~Audio()
{

}

//*****************************************************************************
//
// �I�[�f�B�I���X�g���[���Ƃ��ēǂݍ���
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