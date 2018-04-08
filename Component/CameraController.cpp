﻿//*****************************************************************************
//
// カメラ移動処理 [CameraController.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "CameraController.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
CameraController::CameraController()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
CameraController::~CameraController()
{

}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void CameraController::start()
{
	// mainCameraを取得
	Camera* mainCamera = mMainCamera->getComponent<Camera>("camera");
	// 目標Transを取得
	// CameraControllerはplayer(mGameObject)のコンポーネントなので、直接取得できる
	Transform* trans = mGameObject->getComponent<Transform>("trans");

	// 目標からカメラまでの距離を計算
	mOffsetFromTarget = trans->mPos - mainCamera->mTargetTrans->mPos;
}

//*****************************************************************************
//
// ズーム調整
//
//*****************************************************************************
void CameraController::zoom(float distance)
{
	// カメラを取得
	Camera* mainCamera = mMainCamera->getComponent<Camera>("camera");

	// 新しいoffset距離を計算、範囲を越えてなければoffsetを更新
	D3DXVECTOR3 zoomDistance = mainCamera->mCameraFront * distance;
	D3DXVECTOR3 newOffset = mOffsetFromTarget + zoomDistance;
	float newOffsetDistance = D3DXVec3Length(&newOffset);
	if (newOffsetDistance >= this->mOffsetFromTargetMin && newOffsetDistance <= this->mOffsetFromTargetMax)
	{
		this->mOffsetFromTarget = newOffset;
	}
}

//*****************************************************************************
//
// 回転移動
//
//*****************************************************************************
void CameraController::rotation(float verticalRadians, float horizonalRadians)
{
	// カメラを取得
	Camera* mainCamera = mMainCamera->getComponent<Camera>("camera");
	// ゲーム世界の3軸を取得
	WorldVector worldVector;

	// 水平移動
	D3DXMATRIX horizonalMatrix;
	D3DXMatrixRotationAxis(&horizonalMatrix, &worldVector.worldUp, horizonalRadians);								// 回転行列を作る
	D3DXVec3TransformCoord(&this->mOffsetFromTarget, &this->mOffsetFromTarget, &horizonalMatrix);		// 新しいoffset座標を計算する

	// 垂直移動
	D3DXMATRIX verticalMatrix;
	D3DXMatrixRotationAxis(&verticalMatrix, &mainCamera->mCameraRight, verticalRadians);						// 回転行列を作る
	D3DXVECTOR3 newOffset = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVec3TransformCoord(&newOffset, &this->mOffsetFromTarget, &verticalMatrix);									// 新しいoffset座標を計算する

	D3DXVECTOR3 newOffsetNormalize = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVec3Normalize(&newOffsetNormalize, &newOffset);																					// ベクトルを正規化
	float radianToWorldUp = D3DXVec3Dot(&newOffsetNormalize, &worldVector.worldUp);								// カメラと世界のUpベクトルの角度を外積で計算
	if (radianToWorldUp <= this->mVerticalRadiansMax && radianToWorldUp > this->mVerticalRadiansMin)	// カメラの垂直角度が範囲内ならば
	{
		this->mOffsetFromTarget = newOffset;
	}
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void CameraController::update()
{
	// カメラを左右移動
	if (GetKeyboardPress(DIK_J) == true)
	{

	}
	if (GetKeyboardPress(DIK_L) == true)
	{

	}

	// カメラを上下移動
	if (GetKeyboardPress(DIK_I) == true)
	{

	}
	if (GetKeyboardPress(DIK_K) == true)
	{

	}

	// ズーム拡大
	if (GetKeyboardPress(DIK_U) == true)
		zoom(getGameTimes()->mDeltaTime * this->mZoomSpeed);
	// ズーム縮小
	if (GetKeyboardPress(DIK_O) == true)
		zoom(-getGameTimes()->mDeltaTime * this->mZoomSpeed);
}