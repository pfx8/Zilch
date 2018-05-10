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
	this->mRangeStart = 0.1f;
	this->mRangeEnd = 1000.0f;
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

//*****************************************************************************
//
// ImGuiでCameraのデータを出す
//
//*****************************************************************************
void Camera::drawImGui()
{
	ImGui::Text(u8"カメラ位置");
	float* v1[3] {&this->mCameraPos.x, &this->mCameraPos.y, &this->mCameraPos.z};
	ImGui::InputFloat3("Pos", *v1);
	ImGui::Separator();

	ImGui::Text(u8"カメラ注視点(モデル位置に設定してる)");
	float* v2[3] {&this->mTargetTrans->mPos.x, &this->mTargetTrans->mPos.y, &this->mTargetTrans->mPos.z};
	ImGui::InputFloat3("Look", *v2);
	ImGui::Separator();

	ImGui::Text(u8"注視方向ベクトル");
	float* v3[3] {&this->mCameraFront.x, &this->mCameraFront.y, &this->mCameraFront.z};
	ImGui::DragFloat3("lookV", *v3);
	ImGui::Separator();

	ImGui::Text(u8"右方向ベクトル");
	float* v4[3] {&this->mCameraRight.x, &this->mCameraRight.y, &this->mCameraRight.z};
	ImGui::DragFloat3("rightV", *v4);
	ImGui::Separator();

	ImGui::Text(u8"上方向ベクトル");
	float* v5[3] { &this->mCameraUp.x, &this->mCameraUp.y, &this->mCameraUp.z };
	ImGui::DragFloat3("upV", *v5);
	ImGui::Separator();
}