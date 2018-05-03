//*****************************************************************************
//
// 入力処理 [Input.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "Engine.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// プログラム分けするときに使う
#define	USE_KEYBOARD					// 宣言するとキーボードで操作可能になる
#define	USE_MOUSE						// 宣言するとマウスで操作可能になる
#define	USE_PAD							// 宣言するとパッドで操作可能になる

// ゲームパッドのボタン設定
#define LEFT_STICK_UP			0x00000001l			// 左スティック上(.IY<0)
#define LEFT_STICK_DOWN			0x00000002l			// 左スティック下(.IY>0)
#define LEFT_STICK_LEFT			0x00000004l			// 左スティック左(.IX<0)
#define LEFT_STICK_RIGHT		0x00000008l			// 左スティック右(.IX>0)
#define BUTTON_SQUARE			0x00000010l			// Ａボタン(.rgbButtons[0]&0x80)
#define BUTTON_CROSS			0x00000020l			// Ｂボタン(.rgbButtons[1]&0x80)
#define BUTTON_CIRCLE			0x00000040l			// Ｃボタン(.rgbButtons[2]&0x80)
#define BUTTON_TRIANGLE			0x00000080l			// Ｘボタン(.rgbButtons[3]&0x80)
#define BUTTON_L1				0x00000100l			// Ｙボタン(.rgbButtons[4]&0x80)
#define BUTTON_R1				0x00000200l			// Ｚボタン(.rgbButtons[5]&0x80)
#define BUTTON_L2				0x00000400l			// Ｌボタン(.rgbButtons[6]&0x80)
#define BUTTON_R2				0x00000800l			// Ｒボタン(.rgbButtons[7]&0x80)
#define BUTTON_SHARE			0x00001000l			// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
#define BUTTON_OPTIONS			0x00002000l			// Ｍボタン(.rgbButtons[9]&0x80)
#define RIGHT_STICK_UP			0x00004000l			// 右スティック上(.Z回転<0)
#define RIGHT_STICK_DOWN		0x00008000l			// 右スティック下(.Z回転>0)
#define RIGHT_STICK_LEFT		0x00010000l			// 右スティック左(.IZ<0)
#define RIGHT_STICK_RIGHT		0x00020000l			// 右スティック右(.IZ>0)

#define GAMEPADMAX				4					// 同時に接続するジョイパッドの最大数をセット


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);		// 入力デバイスの初期化
void UpdateInput(void);								// 入力デバイスの更新処理
void UninitInput(void);								// 入力デバイスの終了処理

//*****************************************************************************
//
// キーボード処理
//
//*****************************************************************************
bool GetKeyboardPress(int nKey);			// キーボードのプレス状態を取得
bool GetKeyboardTrigger(int nKey);			// キーボードのトリガー状態を取得
bool GetKeyboardRepeat(int nKey);			// キーボードのリピート状態を取得
bool GetKeyboardRelease(int nKey);			// キーボードのリリ－ス状態を取得

//*****************************************************************************
//
// マウス処理
//
//*****************************************************************************
BOOL IsMouseLeftPressed(void);		// 左クリックした状態を取得
BOOL IsMouseLeftTriggered(void);	// 左クリックした瞬間をチェック
BOOL IsMouseRightPressed(void);		// 右クリックした状態を取得
BOOL IsMouseRightTriggered(void);	// 右クリックした瞬間をチェック
BOOL IsMouseCenterPressed(void);	// 中クリックした状態を取得
BOOL IsMouseCenterTriggered(void);	// 中クリックした瞬間をチェック
long GetMouseX(void);				// マウスが左右に動いた相対値
long GetMouseY(void);				// マウスが前後に動いた相対値
long GetMouseZ(void);				// マウスホイールが動いた相対値

//*****************************************************************************
//
// ゲームパッド処理
//
//*****************************************************************************
BOOL IsButtonPressed(int padNo,DWORD button);		// ゲームパッドのボタンが押した状態を取得
BOOL IsButtonTriggered(int padNo,DWORD button);		// ゲームパッドのボタンが押した瞬間をチェック

#endif