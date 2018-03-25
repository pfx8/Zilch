//*****************************************************************************
//
// �T�E���h���� [Sound.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef ___SOUND_H___
#define ___SOUND_H___

// �}�N����`
enum
{	// �T�E���h�ʂ��i���o�[
	BGM_TITLE,
	BGM_GAME,
	BGM_END,

	SE_HIT,
	SOUND_MAX
};

enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

HRESULT					InitSound( HWND hWnd );	// ������
void					UninitSound();			// ��Еt��
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// �T�E���h�̃��[�h
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// �����ƂɍĐ�
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// �Đ������ǂ���
void					StopSound( LPDIRECTSOUNDBUFFER8 pBuffer);					// �����~�߂�

#endif