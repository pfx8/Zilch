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
	this->field = D3DXToRadian(45);
	this->ratio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;;
	this->rangeStart = 0.1;
	this->rangeEnd = 1000;
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
	D3DXVec3Normalize(&this->cameraFront, &(this->targetTrans->pos - this->cameraPos));
	// 新しい右ベクトルを計算(外積)、そして正規化
	D3DXVec3Cross(&this->cameraRight, &this->cameraFront, &worldVector.worldUp);
	D3DXVec3Normalize(&this->cameraRight, &this->cameraRight);
	// 新しい上ベクトルを計算(外積)、そして正規化
	D3DXVec3Cross(&this->cameraUp, &this->cameraRight, &this->cameraFront);
	D3DXVec3Normalize(&this->cameraUp, &this->cameraUp);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&this->viewMatrix, &this->cameraPos, &(this->targetTrans->pos + D3DXVECTOR3(0.0f, 2.0f, 0.0f)), &this->cameraUp);
	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&this->projectionMatrix, this->field, this->ratio, this->rangeStart, this->rangeEnd);
}