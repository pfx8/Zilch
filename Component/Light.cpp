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

	// ライト強度
	ImGui::TextUnformatted(u8"ライト強度(Max : 20.0)");
	ImGui::DragFloat(u8"Strength", &this->mLightStrength, 0.1f, 1.0f, 20.0f);
	ImGui::Separator();

	// ライト属性
	ImGui::TextUnformatted(u8"アンビエント");
	ImGui::SliderFloat(u8"Ambient", &this->mLightAmbient, 0.0f, 1.0f);
	ImGui::TextUnformatted(u8"ディフューズ");
	ImGui::SliderFloat(u8"Diffuse", &this->mLightDiffuse, 0.0f, 1.0f);
	ImGui::TextUnformatted(u8"スペキュラー");
	ImGui::SliderFloat(u8"Specular", &this->mLightSpecular, 0.0f, 1.0f);
	ImGui::Separator();

	// コンボボックスの幅を設定
	ImGui::PushItemWidth(160);
	ImGui::TextUnformatted(u8"ColorType");
	ImGui::Combo(u8"Type", &this->mCurrentLightType, this->mLight, IM_ARRAYSIZE(this->mLight));
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
	ImGui::Separator();

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
	Transform* trans = this->mGameObject->getComponent<Transform>();
	float* v1[3] = { &trans->mPos.x, &trans->mPos.y, &trans->mPos.z };
	this->mLightPos = trans->mPos;

	switch (this->mLightType)
	{
	case LT_direction:
		ImGui::Separator();
		ImGui::TextUnformatted(u8"ライト方向");
		ImGui::SliderFloat("X", &this->mDirectionLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Y", &this->mDirectionLight.direction.y, -1.0f, 1.0f);
		ImGui::SliderFloat("Z", &this->mDirectionLight.direction.z, -1.0f, 1.0f);

		break;
	case LT_point:
		ImGui::TextUnformatted(u8"位置");
		ImGui::InputFloat3(u8"pos", *v1);
		ImGui::Separator();

		ImGui::TextUnformatted(u8"ポイントライト減衰パラメータ");
		ImGui::InputFloat("Constant", &this->mPointLight.constant);
		ImGui::InputFloat("Linear", &this->mPointLight.linear);
		ImGui::InputFloat("Quadratic", &this->mPointLight.quadratic);

		break;
	case LT_spot:
		ImGui::TextUnformatted(u8"位置");
		ImGui::InputFloat3(u8"Pos", *v1);;
		ImGui::Separator();

		ImGui::TextUnformatted(u8"ライト方向");
		ImGui::SliderFloat("X", &this->mDirectionLight.direction.x, -1.0f, 1.0f);
		ImGui::SliderFloat("Y", &this->mDirectionLight.direction.y, -1.0f, 1.0f);
		ImGui::SliderFloat("Z", &this->mDirectionLight.direction.z, -1.0f, 1.0f);
		ImGui::Separator();

		ImGui::TextUnformatted(u8"スポットベクトルとライトベクトルのコサイン");
		ImGui::SliderFloat("cos", &this->mSpotLight.cutOff, -1.0f, 1.0f);

		break;
	}
}