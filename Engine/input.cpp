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
// マクロ定義
//
//*****************************************************************************
#define	NUM_KEY_MAX			(256)				// 最大キーボードのキー数

// ゲームパッド設定
#define DEADZONE			(2500)				// 各軸の25%を無効ゾーンとする
#define RANGE_MAX			(1000)				// 有効範囲の最大値
#define RANGE_MIN			(-1000)				// 有効範囲の最小値

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);						// キーボード初期化
HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow);					// マウスの初期化
HRESULT InitializePad(void);											// ゲームパッド初期化
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// ゲームパッド検査コールバック

HRESULT UpdateKeyboard(void);		// キーボード更新処理
HRESULT UpdateMouse();				// マウスの更新処理
void UpdatePad(void);				// ゲームパッド更新処理

void UninitKeyboard(void);			// キーボード終了処理
void UninitMouse();					// マウスの終了処理
void UninitPad(void);				// ゲームパッド終了処理

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
LPDIRECTINPUT8				gD3DInput {nullptr};					// IDirectInput8インターフェースへのポインタ

// キーボード用
LPDIRECTINPUTDEVICE8		gDeviceKeyboard {nullptr};				// IDirectInputDevice8インターフェースへのポインタ(キーボード)
BYTE						gKeyState[NUM_KEY_MAX];					// キーボードの状態を受け取るワーク
BYTE						gKeyStateTrigger[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
BYTE						gKeyStateRepeat[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
BYTE						gKeyStateRelease[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
int							gKeyStateRepeatCnt[NUM_KEY_MAX];		// キーボードのリピートカウンタ

// マウス用
static LPDIRECTINPUTDEVICE8 gDeviceMouse {nullptr};					// マウスポインタ
static DIMOUSESTATE2		gMouseState;							// マウスのダイレクトな状態
static DIMOUSESTATE2		gMouseTrigger;							// 押された瞬間だけON

// ゲームパッド用
static LPDIRECTINPUTDEVICE8	gDeviceGamePad[GAMEPADMAX] {nullptr, nullptr, nullptr, nullptr};	// パッドデバイス
static DWORD				gGamePadState[GAMEPADMAX];											// パッド情報（複数対応）
static DWORD				gGamePadTrigger[GAMEPADMAX];										// 押された瞬間だけON
static int					gGamePadCount {0};													// 検出したパッドの数

//*****************************************************************************
//
// 各入力デバイスの初期化
//
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!gD3DInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&gD3DInput, NULL);
	}

	// キーボードの初期化
	InitKeyboard(hInst, hWnd);

 	// マウスの初期化
	InitializeMouse(hInst, hWnd);
	
	// パッドの初期化
	InitializePad();

	return S_OK;
}

//*****************************************************************************
//
// 各入力デバイスの終了処理
//
//*****************************************************************************
void UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// マウスの終了処理
	UninitMouse();

	// パッドの終了処理
	UninitPad();

	// DirectInputオブジェクトをリリース
	RELEASE_POINT(gD3DInput);
}

//*****************************************************************************
//
// 各入力デバイスの更新処理
//
//*****************************************************************************
void UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();
	
	// マウスの更新
	UpdateMouse();
	
	// パッドの更新
	UpdatePad();
}

//*****************************************************************************
//
// キーボードの初期化
//
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = gD3DInput->CreateDevice(GUID_SysKeyboard, &gDeviceKeyboard, NULL);
	if(FAILED(hr) || gDeviceKeyboard == NULL)
	{
		cout << "<Warning>: No keyboard!" << endl;
		return hr;
	}

	// データフォーマットを設定
	hr = gDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		cout << "<Warning>: Can't setup keyboard!" << endl;
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = gDeviceKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		cout << "<Warning>: Keyboard mode error!" << endl;
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	gDeviceKeyboard->Acquire();

	return S_OK;
}

//*****************************************************************************
//
// キーボードの終了処理
//
//*****************************************************************************
void UninitKeyboard(void)
{
	RELEASE_POINT(gDeviceKeyboard);
}

//*****************************************************************************
//
// キーボードの更新
//
//*****************************************************************************
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, gKeyState, NUM_KEY_MAX);

	// デバイスからデータを取得
	hr = gDeviceKeyboard->GetDeviceState(sizeof(gKeyState), gKeyState);
	if(SUCCEEDED(hr))
	{
		for (unsigned int cnt {0}; cnt < NUM_KEY_MAX; cnt++)
		{
			gKeyStateTrigger[cnt] = (keyStateOld[cnt] ^ gKeyState[cnt]) & gKeyState[cnt];
			gKeyStateRelease[cnt] = (keyStateOld[cnt] ^ gKeyState[cnt]) & ~gKeyState[cnt];
			gKeyStateRepeat[cnt] = gKeyStateTrigger[cnt];

			if(gKeyState[cnt])
			{
				gKeyStateRepeatCnt[cnt]++;
				if(gKeyStateRepeatCnt[cnt] >= 20)
				{
					gKeyStateRepeat[cnt] = gKeyState[cnt];
				}
			}
			else
			{
				gKeyStateRepeatCnt[cnt] = 0;
				gKeyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		gDeviceKeyboard->Acquire();
	}

	return S_OK;
}

//*****************************************************************************
//
// キーボードのプレス状態を取得
//
//*****************************************************************************
bool GetKeyboardPress(int key)
{
	return (gKeyState[key] & 0x80) ? true : false;
}

//*****************************************************************************
//
// キーボードのトリガー状態を取得
//
//*****************************************************************************
bool GetKeyboardTrigger(int key)
{
	return (gKeyStateTrigger[key] & 0x80) ? true : false;
}

//*****************************************************************************
//
// キーボードのリピート状態を取得
//
//*****************************************************************************
bool GetKeyboardRepeat(int key)
{
	return (gKeyStateRepeat[key] & 0x80) ? true : false;
}

//*****************************************************************************
//
// キーボードのリリ－ス状態を取得
//
//*****************************************************************************
bool GetKeyboardRelease(int key)
{
	return (gKeyStateRelease[key] & 0x80) ? true : false;
}

//*****************************************************************************
//
// マウスの初期化
//
//*****************************************************************************
HRESULT InitializeMouse(HINSTANCE hInst,HWND hWindow)
{
	HRESULT hr;

	// デバイス作成
	hr = gD3DInput->CreateDevice(GUID_SysMouse,&gDeviceMouse,NULL);
	if(FAILED(hr) || gDeviceMouse==NULL)
	{
		cout << "<Warning>: No mouse!" << endl;
		return hr;
	}

	// データフォーマット設定
	hr = gDeviceMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr))
	{
		cout << "<Warning>: Can't setup mouse!" << endl;
		return hr;
	}

	// 他のアプリと協調モードに設定
	hr = gDeviceMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		cout << "<Warning>: Mouse mode error!" << endl;
		return hr;
	}
	
	// デバイスの設定
	DIPROPDWORD prop;
	
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値　相対値

	hr = gDeviceMouse->SetProperty(DIPROP_AXISMODE,&prop.diph);
	if(FAILED(hr))
	{
		cout << "<Warning>: Mouse property error!" << endl;
		return hr;	
	}
	
	// アクセス権を得る
	gDeviceMouse->Acquire();
	return hr;
}

//*****************************************************************************
//
// マウスの更新処理
//
//*****************************************************************************
HRESULT UpdateMouse()
{
	HRESULT hr;

	// 前回の値保存
	DIMOUSESTATE2 lastMouseState = gMouseState;

	// データ取得
	hr = gDeviceMouse->GetDeviceState(sizeof(gMouseState), &gMouseState);
	if (SUCCEEDED(hr))
	{
		gMouseTrigger.lX = gMouseState.lX;
		gMouseTrigger.lY = gMouseState.lY;
		gMouseTrigger.lZ = gMouseState.lZ;

		// マウスのボタン状態
		for (unsigned int i {0}; i < 8; i++)
		{
			gMouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				gMouseState.rgbButtons[i]) & gMouseState.rgbButtons[i]);
		}
	}
	else
	{
		// 取得失敗
		// アクセス権を得てみる
		hr = gDeviceMouse->Acquire();
	}

	return hr;
}

//*****************************************************************************
//
// マウスの終了処理
//
//*****************************************************************************
void UninitMouse()
{
	if(gDeviceMouse)
	{
		gDeviceMouse->Unacquire();
		gDeviceMouse->Release();
		gDeviceMouse = NULL;
	}
}

//*****************************************************************************
//
// 左クリックした状態を取得
//
//*****************************************************************************
BOOL IsMouseLeftPressed(void)
{
	return (BOOL)(gMouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
}

//*****************************************************************************
//
// 左クリックした瞬間をチェック
//
//*****************************************************************************
BOOL IsMouseLeftTriggered(void)
{
	return (BOOL)(gMouseTrigger.rgbButtons[0] & 0x80);
}

//*****************************************************************************
//
// 右クリックした状態を取得
//
//*****************************************************************************
BOOL IsMouseRightPressed(void)
{
	return (BOOL)(gMouseState.rgbButtons[1] & 0x80);
}

//*****************************************************************************
//
// 右クリックした瞬間をチェック
//
//*****************************************************************************
BOOL IsMouseRightTriggered(void)
{
	return (BOOL)(gMouseTrigger.rgbButtons[1] & 0x80);
}

//*****************************************************************************
//
// 中クリックした状態を取得
//
//*****************************************************************************
BOOL IsMouseCenterPressed(void)
{
	return (BOOL)(gMouseState.rgbButtons[2] & 0x80);
}

//*****************************************************************************
//
// 中クリックした瞬間をチェック
//
//*****************************************************************************
BOOL IsMouseCenterTriggered(void)
{
	return (BOOL)(gMouseTrigger.rgbButtons[2] & 0x80);
}

//*****************************************************************************
//
// マウスが左右に動いた相対値
//
//*****************************************************************************
long GetMouseX(void)
{
	return gMouseState.lX;
}

//*****************************************************************************
//
// マウスが前後に動いた相対値
//
//*****************************************************************************
long GetMouseY(void)
{
	return gMouseState.lY;
}

//*****************************************************************************
//
// マウスホイールが動いた相対値
//
//*****************************************************************************
long GetMouseZ(void)
{
	return gMouseState.lZ;
}


//*****************************************************************************
//
// ゲームパッドの初期化
//
//*****************************************************************************
HRESULT InitializePad(void)
{
	HRESULT hr;

	// ゲームパッド数を設定
	gGamePadCount = 0;
	// ジョイパッドを探す
	gD3DInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。

	for (unsigned int i {0}; i < gGamePadCount; i++)
	{
		// ジョイスティック用のデータ・フォーマットを設定
		hr = gDeviceGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if ( FAILED(hr) )
			return false; // データフォーマットの設定に失敗

		// モードを設定（フォアグラウンド＆非排他モード）
		//result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		//if ( FAILED(result) )
		//	return false; // モードの設定に失敗

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
		gDeviceGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y軸の範囲を設定
		diprg.diph.dwObj		= DIJOFS_Y;
		gDeviceGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z軸の範囲を設定
		diprg.diph.dwObj		= DIJOFS_Z;
		gDeviceGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z回転の範囲を設定
		diprg.diph.dwObj     = DIJOFS_RZ;
		gDeviceGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

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
		gDeviceGamePad[i]->SetProperty( DIPROP_DEADZONE, &dipdw.diph);
		//Y軸の無効ゾーンを設定
		dipdw.diph.dwObj		= DIJOFS_Y;
		gDeviceGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Z軸の無効ゾーンを設定
		dipdw.diph.dwObj		= DIJOFS_Z;
		gDeviceGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Z回転の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_RZ;
		gDeviceGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
			
		//ジョイスティック入力制御開始
		gDeviceGamePad[i]->Acquire();
	}
		
	return true;
}

//*****************************************************************************
//
// ゲームパッド検査コールバック
//
//*****************************************************************************
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
{
	HRESULT hr;

	hr = gD3DInput->CreateDevice(lpddi->guidInstance, &gDeviceGamePad[gGamePadCount++], NULL);

	// 次のデバイスを列挙
	return DIENUM_CONTINUE;
}

//*****************************************************************************
//
// ゲームパッドの更新処理
//
//*****************************************************************************
void UpdatePad(void)
{
	HRESULT hr;
	DIJOYSTATE2 dijs;

	for (unsigned int i {0}; i < gGamePadCount; i++)
	{
		DWORD lastPadState;
		lastPadState = gGamePadState[i];
		gGamePadState[i] = 0x00000000l;	// 初期化

		// ジョイスティックにポールをかける
		hr = gDeviceGamePad[i]->Poll();
		if (FAILED(hr)) 
		{
			hr = gDeviceGamePad[i]->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = gDeviceGamePad[i]->Acquire();
		}

		// デバイス状態を読み取る
		hr = gDeviceGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) 
		{
			hr = gDeviceGamePad[i]->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = gDeviceGamePad[i]->Acquire();
		}

		// LONG lX;		X軸の位置		左アナログスティックの左右
		// LONG lY;		Y軸の位置		左アナログスティックの上下
		// LONG lZ;		Z軸の位置		右アナログスティックの左右
		// LONG lRx;	X軸の回転値		未使用
		// LONG lRy;	Y軸の回転値		未使用
		// LONG lRz;	Z軸の回転値		右アナログスティックの上下

		// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
		//* y-axis (forward)
		if (dijs.lY < 0)					gGamePadState[i] |= LEFT_STICK_UP;
		//* y-axis (backward)
		if (dijs.lY > 0)					gGamePadState[i] |= LEFT_STICK_DOWN;
		//* x-axis (left)
		if (dijs.lX < 0)					gGamePadState[i] |= LEFT_STICK_LEFT;
		//* x-axis (right)
		if (dijs.lX > 0)					gGamePadState[i] |= LEFT_STICK_RIGHT;
		//* z-axis (left)
		if (dijs.lZ < 0)					gGamePadState[i] |= RIGHT_STICK_LEFT;
		//* z-axis (right)
		if (dijs.lZ > 0)					gGamePadState[i] |= RIGHT_STICK_RIGHT;
		//* z-trans (up)
		if (dijs.lRz < 0)					gGamePadState[i] |= RIGHT_STICK_UP;
		//* z-trans (down)
		if (dijs.lRz > 0)					gGamePadState[i] |= RIGHT_STICK_DOWN;


		//* □ボタン
		if (dijs.rgbButtons[0] & 0x80)	gGamePadState[i] |= BUTTON_SQUARE;
		//* ×ボタン
		if (dijs.rgbButtons[1] & 0x80)	gGamePadState[i] |= BUTTON_CROSS;
		//* 〇ボタン
		if (dijs.rgbButtons[2] & 0x80)	gGamePadState[i] |= BUTTON_CIRCLE;
		//* △ボタン
		if (dijs.rgbButtons[3] & 0x80)	gGamePadState[i] |= BUTTON_TRIANGLE;
		//* L1ボタン
		if (dijs.rgbButtons[4] & 0x80)	gGamePadState[i] |= BUTTON_L1;
		//* R1ボタン
		if (dijs.rgbButtons[5] & 0x80)	gGamePadState[i] |= BUTTON_R1;
		//* L2ボタン
		if (dijs.rgbButtons[6] & 0x80)	gGamePadState[i] |= BUTTON_L2;
		//* R2ボタン
		if (dijs.rgbButtons[7] & 0x80)	gGamePadState[i] |= BUTTON_R2;
		//* SHAREボタン
		if (dijs.rgbButtons[8] & 0x80)	gGamePadState[i] |= BUTTON_SHARE;
		//* OPTIONSボタン
		if (dijs.rgbButtons[9] & 0x80)	gGamePadState[i] |= BUTTON_OPTIONS;

		// Trigger設定
		gGamePadTrigger[i] = ((lastPadState ^ gGamePadState[i])	// 前回と違っていて
			& gGamePadState[i]);								// しかも今ONのやつ
	}
}

//*****************************************************************************
//
// ゲームパッドの終了処理	
//
//*****************************************************************************
void UninitPad(void)
{
	for (unsigned int i {0}; i < GAMEPADMAX; i++)
	{
		if ( gDeviceGamePad[i] )
		{
			gDeviceGamePad[i]->Unacquire();
			gDeviceGamePad[i]->Release();
		}
	}
}

//*****************************************************************************
//
// ゲームパッドのボタンが押した状態を取得
//
//*****************************************************************************
BOOL IsButtonPressed(int padNo,DWORD button)
{
	return (button & gGamePadState[padNo]);
}

//*****************************************************************************
//
// ゲームパッドのボタンが押した瞬間をチェック
//
//*****************************************************************************
BOOL IsButtonTriggered(int padNo,DWORD button)
{
	return (button & gGamePadTrigger[padNo]);
}



