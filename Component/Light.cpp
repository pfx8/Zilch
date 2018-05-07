//*****************************************************************************
//
// ライト処理 [Light.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "Light.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Light::Light()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Light::~Light()
{

}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Light::start()
{
	this->mCurrentLightType = this->mLightType;
}

//*****************************************************************************
//
// ImGuiでPointLightのデータを出す
//
//*****************************************************************************
void Light::drawImGui()
{
	// コンボボックスの幅を設定
	ImGui::PushItemWidth(160);
	ImGui::Text(u8"ライトタイプ");
	ImGui::Combo(" ", &this->mCurrentLightType, this->mLight, IM_ARRAYSIZE(this->mLight));
	switch (this->mCurrentLightType)
	{
	case 0:
		this->mLightType = LT_direction;
		break;
	case 1:
		this->mLightType = LT_point;
		break;
	case 2:
		this->mLightType = LT_flash;
		break;
	}

	// 種類によってライトの調整ImGuiを描画
	lightControllerImGui();
}

//*****************************************************************************
//
// 各ライトの調整ImGui
//
//*****************************************************************************
void Light::lightControllerImGui()
{
	// ライト位置入力配列
	float* v1[3] = { &this->mLightPos.x, &this->mLightPos.y, &this->mLightPos.z };

	switch (this->mLightType)
	{
	case LT_direction:
		break;
	case LT_point:
		ImGui::Text(u8"ライト位置");
		ImGui::InputFloat3("pos", *v1);
		ImGui::Separator();

		ImGui::Text(u8"ポイントライト減衰パラメータ");
		ImGui::InputFloat("Constant", &this->mPointLight.constant);
		ImGui::InputFloat("Linear", &this->mPointLight.linear);
		ImGui::InputFloat("Quadratic", &this->mPointLight.quadratic);
		ImGui::Separator();
		break;
	case LT_flash:
		break;
	}
}