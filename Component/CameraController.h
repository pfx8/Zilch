//*****************************************************************************
//
// カメラ移動処理 [CameraController..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CAMERA_CONTROLLER_H_
#define _CAMERA_CONTROLLER_H_

#include "Transform.h"
#include "Camera.h"
#include "../Engine/Engine.h"
#include "../Engine/input.h"
#include "../Engine/GameTimes.h"
#include "../GameObject/GameObject.h"

//*****************************************************************************
//
// クラス宣言
//
// 所属 : Player(GameObject)
//
//*****************************************************************************
class CameraController : public Component
{
private:
	D3DXVECTOR3				mOffsetFromTarget;								// カメラと目標の偏り

	float		mOffsetFromTargetMin = 5.0f;								// プレーヤーとカメラの偏り(半径)の最小値
	float		mOffsetFromTargetMax = 9.0f;								// プレーヤーとカメラの偏り(半径)の最大値
	float		mVerticalRadiansMin = cosf(D3DXToRadian(65.0f));			// カメラの垂直角度の最小値
	float		mVerticalRadiansMax = cosf(D3DXToRadian(-15.0f));			// カメラの垂直角度の最大値
	float		mRotateSpeedHorizonal = 4.0f;								// 水平移動スピード
	float		mRotateSpeedVertical = 2.0f;								// 垂直移動スピード
	float		mZoomSpeed = 0.3f;											// ゾーンスピード
	float		mMoveSpeed = 0.3f;											// カメラ移動スピード

public:
	GameObject*				mMainCamera;					// マインカメラ

	CameraController();
	~CameraController();

	void start();													// 初期化
	void update();													// 更新
	void inputUpdate();												// 入力更新
	void zoom(float distance);										// ズーム調整
	void rotation(float verticalRadians, float horizonalRadians);	// 回転移動
	void move(float distance, bool isVertical);						// 位置移動
	void drawImGui();												// ImGuiでCameraControllerのデータを出す
};
#endif // !_CAMERA_H_