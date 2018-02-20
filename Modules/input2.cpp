//*****************************************************************************
//
// 入力処理 [Input.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "input.h"


//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
InputDevice::InputDevice()
{
	this->input = NULL;
	this->keyBoard = NULL;
	this->gamePad = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
InputDevice::~InputDevice()
{
	RELEASE_POINT(this->input);
	RELEASE_POINT(this->keyBoard);
	RELEASE_POINT(this->gamePad);
}

//*****************************************************************************
//
// 入力デバイスを初期化
//
//*****************************************************************************
HRESULT InputDevice::InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// DirectInputオブジェクトの作成
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&this->input, NULL);

	if (FAILED(hr))
	{
		std::cout << "[Error] InputDevice Init Failed!" << std::endl;
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//
// キーボードを初期化
//
//*****************************************************************************
HRESULT  InputDevice::InitKeyBoard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = this->input->CreateDevice(GUID_SysKeyboard, &this->keyBoard, NULL);

	if (FAILED(hr) || this->keyBoard == NULL)
	{
		std::cout << "[Error] Initialization keyboard ... failed!" << std::endl;
		return hr;
	}

	// データフォーマットを設定
	hr = this->keyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		std::cout << "[Error] Set keyboard data format ... failed!" << std::endl;
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = this->keyBoard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		std::cout << "[Error] Set keyboard cooperative ... failed!" << std::endl;
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	this->keyBoard->Acquire();

	return S_OK;
}

//*****************************************************************************
//
// ゲームパッドを初期化
//
//*****************************************************************************
HRESULT  InputDevice::InitGamePad()
{

}

//=============================================================================
// キーボードの更新
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	// デバイスからデータを取得
	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
	if(SUCCEEDED(hr))
	{
		for(int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];
			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];

			if(g_keyState[cnt])
			{
				g_keyStateRepeatCnt[cnt]++;
				if(g_keyStateRepeatCnt[cnt] >= 20)
				{
					g_keyStateRepeat[cnt] = g_keyState[cnt];
				}
			}
			else
			{
				g_keyStateRepeatCnt[cnt] = 0;
				g_keyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}


//================================================= game pad
//---------------------------------------- コールバック関数
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID )
{
	HRESULT result;

	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
	return DIENUM_CONTINUE;	// 次のデバイスを列挙

}
//---------------------------------------- 初期化
HRESULT InitializePad(void)			// パッド初期化
{
	HRESULT		result;
	int			i;

	padCount = 0;
	// ジョイパッドを探す
	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。

	for ( i=0 ; i<padCount ; i++ ) {
		// ジョイスティック用のデータ・フォーマットを設定
		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if ( FAILED(result) )
			return false; // データフォーマットの設定に失敗

		// モードを設定（フォアグラウンド＆非排他モード）
//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//		if ( FAILED(result) )
//			return false; // モードの設定に失敗

		// 軸の値の範囲を設定
		// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
		// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
		// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドの性能による)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize		= sizeof(diprg); 
		diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
		diprg.diph.dwHow		= DIPH_BYOFFSET; 
		diprg.lMin				= RANGE_MIN;
		diprg.lMax				= RANGE_MAX;
		// X軸の範囲を設定
		diprg.diph.dwObj		= DIJOFS_X; 
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y軸の範囲を設定
		diprg.diph.dwObj		= DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z軸の範囲を設定
		diprg.diph.dwObj		= DIJOFS_Z;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 各軸ごとに、無効のゾーン値を設定する。
		// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
		// 指定する値は、10000に対する相対値(2000なら20パーセント)。
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize	= sizeof(dipdw.diph);
		dipdw.diph.dwHow		= DIPH_BYOFFSET;
		dipdw.dwData			= DEADZONE;
		//X軸の無効ゾーンを設定
		dipdw.diph.dwObj		= DIJOFS_X;
		pGamePad[i]->SetProperty( DIPROP_DEADZONE, &dipdw.diph);
		//Y軸の無効ゾーンを設定
		dipdw.diph.dwObj		= DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Z軸の無効ゾーンを設定
		dipdw.diph.dwObj		= DIJOFS_Z;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
			
		//ジョイスティック入力制御開始
		pGamePad[i]->Acquire();
	}
		
	return true;

}
//------------------------------------------- 終了処理
void UninitPad(void)
{
	for (int i=0 ; i<GAMEPADMAX ; i++) {
		if ( pGamePad[i] )
		{
			pGamePad[i]->Unacquire();
			pGamePad[i]->Release();
		}
	}

}

//------------------------------------------ 更新
void UpdatePad(void)
{
	HRESULT			result;
	DIJOYSTATE2		dijs;
	int				i;

	for ( i=0 ; i<padCount ; i++ ) 
	{
		DWORD lastPadState;
		lastPadState = padState[i];
		padState[i] = 0x00000000l;	// 初期化

		result = pGamePad[i]->Poll();	// ジョイスティックにポールをかける
		if ( FAILED(result) ) {
			result = pGamePad[i]->Acquire();
			while ( result == DIERR_INPUTLOST )
				result = pGamePad[i]->Acquire();
		}

		result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
		if ( result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED ) {
			result = pGamePad[i]->Acquire();
			while ( result == DIERR_INPUTLOST )
				result = pGamePad[i]->Acquire();
		}

		// LONG lX;		X軸の位置		左アナログスティックの左右
		// LONG lY;		Y軸の位置		左アナログスティックの上下
		// LONG lZ;		Z軸の位置		右アナログスティックの左右
		// LONG lRx;	X軸の回転値		未使用
		// LONG lRy;	Y軸の回転値		未使用
		// LONG lRz;	Z軸の回転値		右アナログスティックの上下

		// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
		//* y-axis (forward)
		if ( dijs.lY < 0 )					padState[i] |= LEFT_STICK_UP;
		//* y-axis (backward)
		if ( dijs.lY > 0 )					padState[i] |= LEFT_STICK_DOWN;
		//* x-axis (left)
		if ( dijs.lX < 0 )					padState[i] |= LEFT_STICK_LEFT;
		//* x-axis (right)
		if ( dijs.lX > 0 )					padState[i] |= LEFT_STICK_RIGHT;
		//* z-axis (left)
		if ( dijs.lZ < 0 )					padState[i] |= RIGHT_STICK_LEFT;
		//* z-axis (right)
		if ( dijs.lZ > 0 )					padState[i] |= RIGHT_STICK_RIGHT;
		//* z-trans (up)
		if (dijs.lRz < 0)					padState[i] |= RIGHT_STICK_UP;
		//* z-trans (down)
		if (dijs.lRz > 0)					padState[i] |= RIGHT_STICK_DOWN;
		

		//* □ボタン
		if ( dijs.rgbButtons[0] & 0x80 )	padState[i] |= BUTTON_SQUARE;
		//* ×ボタン
		if ( dijs.rgbButtons[1] & 0x80 )	padState[i] |= BUTTON_CROSS;
		//* 〇ボタン
		if ( dijs.rgbButtons[2] & 0x80 )	padState[i] |= BUTTON_CIRCLE;
		//* △ボタン
		if ( dijs.rgbButtons[3] & 0x80 )	padState[i] |= BUTTON_TRIANGLE;
		//* L1ボタン
		if ( dijs.rgbButtons[4] & 0x80 )	padState[i] |= BUTTON_L1;
		//* R1ボタン
		if ( dijs.rgbButtons[5] & 0x80 )	padState[i] |= BUTTON_R1;
		//* L2ボタン
		if ( dijs.rgbButtons[6] & 0x80 )	padState[i] |= BUTTON_L2;
		//* R2ボタン
		if ( dijs.rgbButtons[7] & 0x80 )	padState[i] |= BUTTON_R2;
		//* SHAREボタン
		if ( dijs.rgbButtons[8] & 0x80 )	padState[i] |= BUTTON_SHARE;
		//* OPTIONSボタン
		if ( dijs.rgbButtons[9] & 0x80 )	padState[i] |= BUTTON_OPTIONS;

		// Trigger設定
		padTrigger[i] = ((lastPadState ^ padState[i])	// 前回と違っていて
						& padState[i]);					// しかも今ONのやつ
		
	}

}
//----------------------------------------------- 検査
BOOL IsButtonPressed(int padNo,DWORD button)
{
	return (button & padState[padNo]);
}

BOOL IsButtonTriggered(int padNo,DWORD button)
{
	return (button & padTrigger[padNo]);
}



