//*****************************************************************************
//
// サウンド処理 [Sound.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef ___SOUND_H___
#define ___SOUND_H___

// マクロ定義
enum
{	// サウンド通しナンバー
	BGM_TITLE,
	BGM_GAME,
	BGM_END,

	SE_HIT,
	SOUND_MAX
};

enum
{	// 再生用フラグ
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

HRESULT					InitSound( HWND hWnd );	// 初期化
void					UninitSound();			// 後片付け
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// サウンドのロード
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// 音ごとに再生
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// 再生中かどうか
void					StopSound( LPDIRECTSOUNDBUFFER8 pBuffer);					// 音を止める

#endif