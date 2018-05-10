//*****************************************************************************
//
// 変換処理 [Transform.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "Transform.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Transform::Transform()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Transform::~Transform()
{

}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void Transform::update()
{
	// 計算用マトリックス
	D3DXMATRIX mtxScl, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->mWorldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, mScl.x, mScl.y, mScl.z);
	//D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &mtxScl);
	this->mWorldMatrix = this->mWorldMatrix * mtxScl;

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&this->mRotMatrix, mRot.y, mRot.x, mRot.z);
	//D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &this->mRotMatrix);
	this->mWorldMatrix = this->mWorldMatrix * this->mRotMatrix;

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, mPos.x, mPos.y, mPos.z);
	//D3DXMatrixMultiply(&this->mWorldMatrix, &this->mWorldMatrix, &mtxTranslate);
	this->mWorldMatrix = this->mWorldMatrix * mtxTranslate;
}

//*****************************************************************************
//
// ImGuiでTransformのデータを出す
//
//*****************************************************************************
void Transform::drawImGui()
{
	ImGui::Text(u8"スケール(X,Y,Z)");
	float* v1[3] {&this->mScl.x, &this->mScl.y, &this->mScl.z};
	ImGui::InputFloat3("Scl", *v1);
	ImGui::Separator();

	ImGui::Text(u8"回転");
	ImGui::SliderFloat("X", &this->mRot.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Y", &this->mRot.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Z", &this->mRot.z, -1.0f, 1.0f);
	ImGui::Separator();

	ImGui::Text(u8"位置(X,Y,Z)");
	float* v2[3] {&this->mPos.x, &this->mPos.y, &this->mPos.z};
	ImGui::InputFloat3("Tran", *v2);
}