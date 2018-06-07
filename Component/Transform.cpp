//*****************************************************************************
//
// 変換処理 [Transform.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "Transform.h"

#include "Billboard.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Transform::Transform(void)
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Transform::~Transform(void)
{

}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void Transform::update(void)
{
	// 計算用マトリックス
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->mWorldMatrix);
	D3DXMatrixIdentity(&this->mNormalMatrix);

	// チェックビルボード
	//if (this->mParentGameObject->getComponent<Billboard>() != nullptr)
	//{
	//	this->mWorldMatrix = this->mParentGameObject->getComponent<Billboard>()->setBillboard();
	//}

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, mScl.x, mScl.y, mScl.z);
	this->mWorldMatrix *= mtxScl;
	this->mNormalMatrix *= mtxScl;

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(mRot.y), D3DXToRadian(mRot.x), D3DXToRadian(mRot.z));
	this->mWorldMatrix *= mtxRot;
	this->mNormalMatrix *= mtxRot;

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, mPos.x, mPos.y, mPos.z);
	this->mWorldMatrix *= mtxTranslate;
}

//*****************************************************************************
//
// ImGuiでTransformのデータを出す
//
//*****************************************************************************
void Transform::drawImGui(void)
{
	ImGui::Text(u8"スケール(X,Y,Z)");
	float* v1[3] = { &this->mScl.x, &this->mScl.y, &this->mScl.z };
	ImGui::InputFloat3("Scl", *v1);
	ImGui::Separator();

	ImGui::Text(u8"回転");

	ImGui::PushItemWidth(200);
	ImGui::SliderFloat("X", &this->mRot.x, 0.0f, 360.0f);
	ImGui::SliderFloat("Y", &this->mRot.y, 0.0f, 360.0f);
	ImGui::SliderFloat("Z", &this->mRot.z, 0.0f, 360.0f);
	ImGui::Separator();

	ImGui::Text(u8"位置(X,Y,Z)");
	float* v2[3] = { &this->mPos.x, &this->mPos.y, &this->mPos.z };
	ImGui::InputFloat3("Pos", *v2);
}