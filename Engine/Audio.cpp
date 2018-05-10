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
	// ���ʕϐ�
	FMOD_RESULT result;

	// FMOD�V�X�e����������
	result = FMOD::System_Create(&this->mSystem);
	if (result != FMOD_OK)
	{
		cout << "[Error] FMOD::System_Create ... fail!" << endl << FMOD_ErrorString(result);
		return E_FAIL;
	}

	// FMOD��������
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
HRESULT Audio::createStream(const string path, FMOD_MODE mode)
{
	FMOD_RESULT result;

	// �T�E���h��ǂݍ���
	FMOD::Sound* sound;
	result = this->mSystem->createStream(path.c_str(), mode, 0, &sound);
	if (result != FMOD_OK)
	{
		cout << "[Error] FMOD system create stream ... " << FMOD_ErrorString(result);
		return E_FAIL;
	}

	string fileName {path.substr(path.find_last_of("//") + 1, path.find_first_of("."))};
	// �T�E���h�}�b�v�ɓ����
	this->mSoundsMap.insert(make_pair(fileName, sound));

	return S_OK;
}

//*****************************************************************************
//
// �v���[�T�E���h
//
//*****************************************************************************
HRESULT Audio::playAudio(string name)
{
	FMOD_RESULT result;

	// ���O����T�E���h���擾
	FMOD::Sound* sound;
	if (this->mSoundsMap.find(name) != this->mSoundsMap.end())
	{
		sound = this->mSoundsMap[name];
	}
	else
	{
		return E_FAIL;
	}

	// �v���[�T�E���h
	//result = PlaySound(sound, )
}

//*****************************************************************************
//
// �X�VFMOD
//
//*****************************************************************************
void Audio::update()
{

}