//*****************************************************************************
//
// ポイントライト処理 [PointLight.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "PointLight.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
PointLight::PointLight()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
PointLight::~PointLight()
{

}

//*****************************************************************************
//
// ライト更新
//
//*****************************************************************************
void PointLight::update()
{
	// ライト属性
	ImGui::Begin("Light");
	ImGui::Text("PointLight");
	float* v[3] = { &this->mLightPos.x, &this->mLightPos.y, &this->mLightPos.z };
	ImGui::InputFloat3("position", *v);
	ImGui::End();
}