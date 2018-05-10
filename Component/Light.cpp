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
	// ライトカラー
	ImGui::ColorEdit4(u8"ライトカラー", this->mLightColor);
	ImGui::Separator();

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
		this->mLightType = LT_spot;
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
	float* v1[3] {&this->mLightPos.x, &this->mLightPos.y, &this->mLightPos.z};

	switch (this->mLightType)
	{
	case LT_direction:
		ImGui::Text(u8"ライト方向");
		ImGui::SliderFloat("X", &this->mDirectionLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Y", &this->mDirectionLight.direction.y, -1.0f, 1.0f);
		ImGui::SliderFloat("Z", &this->mDirectionLight.direction.z, -1.0f, 1.0f);

		break;
	case LT_point:
		ImGui::Text(u8"ライト位置");
		ImGui::InputFloat3("pos", *v1);
		ImGui::Separator();

		ImGui::Text(u8"ポイントライト減衰パラメータ");
		ImGui::InputFloat("Constant", &this->mPointLight.constant);
		ImGui::InputFloat("Linear", &this->mPointLight.linear);
		ImGui::InputFloat("Quadratic", &this->mPointLight.quadratic);

		break;
	case LT_spot:
		ImGui::Text(u8"ライト方向");
		ImGui::SliderFloat("X", &this->mDirectionLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Y", &this->mDirectionLight.direction.y, -1.0f, 1.0f);
		ImGui::SliderFloat("Z", &this->mDirectionLight.direction.z, -1.0f, 1.0f);
		ImGui::Separator();

		ImGui::Text(u8"スポットベクトルとライトベクトルのコサイン");
		ImGui::SliderFloat("cos", &this->mSpotLight.cutOff, -1.0f, 1.0f);

		break;
	}
}