//*****************************************************************************
//
// カメラコントローラ処理 [CameraController.cpp]
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
	this->mSceneCurrentCamera = this->mGameObject->mScene->mCurrentCamera;
}

//*****************************************************************************
//
// ズーム調整
//
//*****************************************************************************
void CameraController::zoom(float distance)
{
	// 新しいoffset距離を計算、範囲を越えてなければoffsetを更新
	D3DXVECTOR3 zoomDistance = this->mSceneCurrentCamera->mCameraFront * distance;
	D3DXVECTOR3 newOffset = this->mOffsetFromTarget + zoomDistance;

	float newOffsetDistance = D3DXVec3Length(&newOffset);
	if (this->mSceneCurrentCamera->mIsZoomLimited == true)
	{
		if (newOffsetDistance >= this->mOffsetFromTargetMin && newOffsetDistance <= this->mOffsetFromTargetMax)
		{
			this->mOffsetFromTarget = newOffset;
		}
	}
	else
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
	// ゲーム世界の3軸を取得
	WorldVector worldVector;

	// 水平移動
	D3DXMATRIX horizonalMatrix;
	D3DXMatrixRotationAxis(&horizonalMatrix, &worldVector.worldUp, horizonalRadians);					// 回転行列を作る(世界のY軸に中心して回転)
	D3DXVec3TransformCoord(&this->mOffsetFromTarget, &this->mOffsetFromTarget, &horizonalMatrix);		// 新しいoffset座標を計算する

	// 垂直移動
	D3DXMATRIX verticalMatrix;
	D3DXMatrixRotationAxis(&verticalMatrix, &this->mSceneCurrentCamera->mCameraRight, verticalRadians);	// 回転行列を作る(カメラの右軸に中心して回転)
	D3DXVECTOR3 newOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3TransformCoord(&newOffset, &this->mOffsetFromTarget, &verticalMatrix);						// 新しいoffset座標を計算する

	D3DXVECTOR3 newOffsetNormalize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&newOffsetNormalize, &newOffset);													// ベクトルを正規化
	float radianToWorldUp { D3DXVec3Dot(&newOffsetNormalize, &worldVector.worldUp) };					// カメラと世界のUpベクトルの角度を外積で計算

	if (this->mSceneCurrentCamera->mIsVerticalLimited == true)
	{	
		// カメラの垂直角度が範囲内ならば
		if (radianToWorldUp <= this->mVerticalRadiansMax && radianToWorldUp > this->mVerticalRadiansMin)
		{
			this->mOffsetFromTarget = newOffset;
		}
	}
	else
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
	// 目標からカメラまでの距離を計算
	this->mOffsetFromTarget = this->mSceneCurrentCamera->mCameraPos - this->mSceneCurrentCamera->mTargetPos;

	// 入力更新
	inputUpdate();

	// カメラを更新
	this->mSceneCurrentCamera->mCameraPos = this->mSceneCurrentCamera->mTargetPos + this->mOffsetFromTarget;
}

//*****************************************************************************
//
// 位置移動
//
//*****************************************************************************
void CameraController::move(float sign, bool isFront)
{
	// ターゲットとのオフセット座標とターゲットの座標を更新
	if (isFront)
	{
		// 前後移動
		this->mOffsetFromTarget += this->mSceneCurrentCamera->mCameraFront * 0.1 * sign;
		this->mSceneCurrentCamera->mTargetPos += this->mSceneCurrentCamera->mCameraFront * 0.1 * sign;
	}
	else
	{
		// 左右移動
		this->mOffsetFromTarget += D3DXVECTOR3(0.3f, 0.0f, 0.0f) * sign;
		this->mSceneCurrentCamera->mTargetPos += D3DXVECTOR3(0.3f, 0.0f, 0.0f) * sign;
	}
}

//*****************************************************************************
//
// 入力更新
//
//*****************************************************************************
void CameraController::inputUpdate()
{
	// カメラを左右移動
	if ((IsMouseLeftPressed() && GetMouseX() > this->mMouseIsMoving) || IsButtonPressed(0, RIGHT_STICK_LEFT))
	{
		rotation(0.0f, D3DXToRadian(this->mRotateSpeedHorizonal));
	}
	if ((IsMouseLeftPressed() && GetMouseX() < -this->mMouseIsMoving) || IsButtonPressed(0, RIGHT_STICK_RIGHT))
	{
		rotation(0.0f, -D3DXToRadian(this->mRotateSpeedHorizonal));
	}

	// カメラを上下移動
	if ((IsMouseLeftPressed() && GetMouseY() > this->mMouseIsMoving) || IsButtonPressed(0, RIGHT_STICK_UP))
	{
		rotation(-D3DXToRadian(this->mRotateSpeedVertical), 0.0f);
	}
	if ((IsMouseLeftPressed() && GetMouseY() < -this->mMouseIsMoving) || IsButtonPressed(0, RIGHT_STICK_DOWN))
	{
		rotation(D3DXToRadian(this->mRotateSpeedVertical), 0.0f);
	}

	// ズーム拡大
	if (GetMouseZ() > this->mMouseIsMoving || IsButtonPressed(0, BUTTON_L1))
	{
		zoom(this->mZoomSpeed);
	}
	// ズーム縮小
	if (GetMouseZ() < -this->mMouseIsMoving || IsButtonPressed(0, BUTTON_R1))
	{
		zoom(-this->mZoomSpeed);
	}

	// カメラ移動(前)
	if (GetKeyboardPress(DIK_W) || IsButtonPressed(0, LEFT_STICK_UP))
	{
		move(1, true);
	}
	// カメラ移動(後)
	if (GetKeyboardPress(DIK_S) || IsButtonPressed(0, LEFT_STICK_DOWN))
	{
		move(-1, true);
	}
	// カメラ移動(左)
	if (GetKeyboardPress(DIK_A) || IsButtonPressed(0, LEFT_STICK_LEFT))
	{
		move(this->mMoveSpeed, false);
	}
	// カメラ移動(右)
	if (GetKeyboardPress(DIK_D) || IsButtonPressed(0, LEFT_STICK_RIGHT))
	{
		move(-this->mMoveSpeed, false);
	}
}

//*****************************************************************************
//
// ImGuiでCameraControllerのデータを出す
//
//*****************************************************************************
void CameraController::drawImGui()
{
	// 操作の説明
	ImGui::Text(u8"マウス左ボタン+");
}