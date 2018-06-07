//*****************************************************************************
//
// ビルボード処理 [Billboard.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "Billboard.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Billboard::Billboard(void)
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Billboard::~Billboard(void)
{

}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Billboard::start(void)
{
	// 位置情報をGameObjectから取得
	this->mTrans = this->mParentGameObject->getComponent<Transform>();
}

//*****************************************************************************
//
// ビルボード行列を生成
//
//*****************************************************************************
D3DXMATRIX Billboard::setBillboard(void)
{
	D3DXMATRIX viewMatrix = this->mSceneCurrentCamera->mViewMatrix;

	// ビルボード行列を作る
	D3DXMatrixIdentity(&this->mBillboardMatrix);

	this->mBillboardMatrix._11 = viewMatrix._11;
	this->mBillboardMatrix._13 = viewMatrix._13;
	this->mBillboardMatrix._31 = viewMatrix._31;
	this->mBillboardMatrix._33 = viewMatrix._33;

	// 逆行列を計算
	D3DXMatrixInverse(&this->mBillboardMatrix, NULL, &this->mBillboardMatrix);

	// ビルボードのワールド変換行列を更新
	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	temp = this->mBillboardMatrix * temp;

	return temp;
}

//*****************************************************************************
//
// GUIパネル
//
//*****************************************************************************
void Billboard::drawImGui(void)
{
	ImGui::Text(u8"ワールド変換行列");
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mTrans->mWorldMatrix._11, this->mTrans->mWorldMatrix._12, this->mTrans->mWorldMatrix._13, this->mTrans->mWorldMatrix._14);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mTrans->mWorldMatrix._21, this->mTrans->mWorldMatrix._22, this->mTrans->mWorldMatrix._23, this->mTrans->mWorldMatrix._24);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mTrans->mWorldMatrix._31, this->mTrans->mWorldMatrix._32, this->mTrans->mWorldMatrix._33, this->mTrans->mWorldMatrix._34);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mTrans->mWorldMatrix._41, this->mTrans->mWorldMatrix._42, this->mTrans->mWorldMatrix._43, this->mTrans->mWorldMatrix._44);
	ImGui::Separator();

	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mBillboardMatrix._11, this->mBillboardMatrix._12, this->mBillboardMatrix._13, this->mBillboardMatrix._14);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mBillboardMatrix._21, this->mBillboardMatrix._22, this->mBillboardMatrix._23, this->mBillboardMatrix._24);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mBillboardMatrix._31, this->mBillboardMatrix._32, this->mBillboardMatrix._33, this->mBillboardMatrix._34);
	ImGui::Text("%.2f    %.2f    %.2f    %.2f", this->mBillboardMatrix._41, this->mBillboardMatrix._42, this->mBillboardMatrix._43, this->mBillboardMatrix._44);

}