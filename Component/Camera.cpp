//*****************************************************************************
//
// カメラ処理 [Camera.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Camera.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Camera::Camera()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Camera::~Camera()
{

}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Camera::start()
{
	this->mField = D3DXToRadian(45);
	this->mRatio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	this->mRangeStart = 0.1;
	this->mRangeEnd = 1000;
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void Camera::update()
{
	// 世界ベクトルを取得
	WorldVector worldVector;
	// デバッグメッセージを取得
	DebugMessage* debugMessage = getDebugMessage();

	// 新しい向きベクトルを計算
	D3DXVec3Normalize(&this->mCameraFront, &(this->mTargetTrans->mPos - this->mCameraPos));
	// 新しい右ベクトルを計算(外積)、そして正規化
	D3DXVec3Cross(&this->mCameraRight, &this->mCameraFront, &worldVector.worldUp);
	D3DXVec3Normalize(&this->mCameraRight, &this->mCameraRight);
	// 新しい上ベクトルを計算(外積)、そして正規化
	D3DXVec3Cross(&this->mCameraUp, &this->mCameraRight, &this->mCameraFront);
	D3DXVec3Normalize(&this->mCameraUp, &this->mCameraUp);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&this->mViewMatrix, &this->mCameraPos, &(this->mTargetTrans->mPos + D3DXVECTOR3(0.0f, 2.0f, 0.0f)), &this->mCameraUp);
	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&this->mProjectionMatrix, this->mField, this->mRatio, this->mRangeStart, this->mRangeEnd);
}