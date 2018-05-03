//*****************************************************************************
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
	D3DXMatrixRotationAxis(&horizonalMatrix, &worldVector.worldUp, horizonalRadians);								// 回転行列を作る(世界のY軸に中心して回転)
	D3DXVec3TransformCoord(&this->mOffsetFromTarget, &this->mOffsetFromTarget, &horizonalMatrix);		// 新しいoffset座標を計算する

	// 垂直移動
	D3DXMATRIX verticalMatrix;
	D3DXMatrixRotationAxis(&verticalMatrix, &mainCamera->mCameraRight, verticalRadians);						// 回転行列を作る(カメラの右軸に中心して回転)
	D3DXVECTOR3 newOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&newOffset, &this->mOffsetFromTarget, &verticalMatrix);									// 新しいoffset座標を計算する

	D3DXVECTOR3 newOffsetNormalize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	// mainCameraを取得
	Camera* mainCamera = mMainCamera->getComponent<Camera>("camera");

	// 目標からカメラまでの距離を計算
	mOffsetFromTarget = mainCamera->mCameraPos - mainCamera->mTargetTrans->mPos;

	// 入力更新
	inputUpdate();

	// カメラを更新
	mainCamera->mCameraPos = mainCamera->mTargetTrans->mPos + mOffsetFromTarget;
}

//*****************************************************************************
//
// 入力更新
//
//*****************************************************************************
void CameraController::inputUpdate()
{
	// カメラを左右移動
	if ((IsMouseLeftPressed() && GetMouseX() > 10) || IsButtonPressed(0, RIGHT_STICK_LEFT))
	{
		rotation(0.0f, D3DXToRadian(this->mRotateSpeedHorizonal));
	}
	if ((IsMouseLeftPressed() && GetMouseX() < -10) || IsButtonPressed(0, RIGHT_STICK_RIGHT))
	{
		rotation(0.0f, -D3DXToRadian(this->mRotateSpeedHorizonal));
	}

	// カメラを上下移動
	if ((IsMouseLeftPressed() && GetMouseY() > 10) || IsButtonPressed(0, RIGHT_STICK_UP))
	{
		rotation(-D3DXToRadian(this->mRotateSpeedVertical), 0.0f);
	}
	if ((IsMouseLeftPressed() && GetMouseY() < -10) || IsButtonPressed(0, RIGHT_STICK_DOWN))
	{
		rotation(D3DXToRadian(this->mRotateSpeedVertical), 0.0f);
	}

	// ズーム拡大
	if (GetMouseZ() > 0 || IsButtonPressed(0, BUTTON_L1))
	{
		zoom(this->mZoomSpeed);
	}
	// ズーム縮小
	if (GetMouseZ() < 0 || IsButtonPressed(0, BUTTON_R1))
	{
		zoom(-this->mZoomSpeed);
	}
}