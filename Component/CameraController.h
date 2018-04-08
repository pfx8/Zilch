﻿//*****************************************************************************
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
	float		mOffsetFromTargetMin = 15.0f;		// プレーヤーとカメラの偏りの最小値
	float		mOffsetFromTargetMax = 25.0f;		// プレーヤーとカメラの偏りの最大値

	float		mVerticalRadiansMin = cosf(D3DXToRadian(15.0f));			// カメラの垂直角度の最小値
	float		mVerticalRadiansMax = cosf(D3DXToRadian(75.0f));		// カメラの垂直角度の最大値

	float		mRotateSpeedHorizonal = 2.0f;			// 水平移動スピード
	float		mRotateSpeedVertical = 1.0f;				// 垂直移動スピード
	float		mZoomSpeed = 2.0f;								// ゾーンスピード

	D3DXVECTOR3			mOffsetFromTarget;			// カメラと目標の偏り

public:
	GameObject*				mMainCamera;					// マインカメラ

	CameraController();
	~CameraController();

	void start();														// 初期化
	void update();													// 更新
	void zoom(float distance);							// ズーム調整
	void rotation(float verticalRadians, float horizonalRadians);	// 回転移動
};
#endif // !_CAMERA_H_