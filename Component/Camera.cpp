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
	this->mRatio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;;
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
	
	mCameraTarget = mTargetTrans->mPos;
	// 新しい向きベクトルを計算
	D3DXVec3Normalize(&mCameraFront, &(mCameraTarget - mCameraPos));
	// 新しい右ベクトルを計算(外積)、そして正規化
	D3DXVec3Cross(&mCameraRight, &mCameraFront, &worldVector.worldUp);
	D3DXVec3Normalize(&mCameraRight, &mCameraRight);
	// 新しい上ベクトルを計算(外積)、そして正規化
	D3DXVec3Cross(&mCameraUp, &mCameraRight, &mCameraFront);
	D3DXVec3Normalize(&mCameraUp, &mCameraUp);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mViewMatrix, &mCameraPos, &mCameraTarget, &this->mCameraUp);
	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&mProjectionMatrix, mField, mRatio, mRangeStart, mRangeEnd);

	/*debugMessage->setPosMessage("cameraFront", mCameraFront);
	debugMessage->setPosMessage("cameraRight", mCameraRight);
	debugMessage->setPosMessage("cameraUp", mCameraUp);*/
	debugMessage->setPosMessage("cameraPos", mCameraPos);
	debugMessage->setPosMessage("cameraTarget", mCameraTarget);
	debugMessage->setPosMessage("cameraAb", D3DXVECTOR3(this->mRangeStart, this->mRangeEnd, this->mField));
}