//*****************************************************************************
//
// ライト処理 [Light.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Component.h"

#include "Engine/Engine.h"

//*****************************************************************************
//
// 各ライト構造体
//
//*****************************************************************************
struct DirectionLight
{
	D3DXVECTOR3			direction;
};

struct PointLight
{
	// ポイントライト減衰公式
	// Luminosity = 1 / Attenuation
	// Attenuation = Constant + Linear * Distance + Quadratic * Distance ^ 2
	// http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation

	// 明度 = 1 / 減衰値
	// 減衰値 = 1.0/(constant + linear * d + quadratic * d^2)
	float				constant;			// 定数、いつも1.0で
	float				linear;				// リニア的で強度を減少させる
	float				quadratic;			// 二次で強度を減少させる
};

struct SpotLight
{
	D3DXVECTOR3			direction;
	float				cutOff;				// スポットベクトルとライトベクトルのコサイン値
	bool				isSmooth;			// スムースチェック
};

//*****************************************************************************
//
// 列挙体
//
//*****************************************************************************
enum LightType
{
	LT_direction,
	LT_point,
	LT_spot,
};

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Light : public Component
{
private:
	int					mCurrentLightType;
	const char*			mLight[3] {u8"指向性ライト", u8"ポイントライト", u8"スポットライト"};

	void start();		// 初期化

public:
	LightType			mLightType;			// ライトタイプ
	D3DXVECTOR3			mLightPos;			// ライトの位置
	D3DXVECTOR4			mLightColor;		// ライトのカラー

	PointLight			mPointLight;		// ポイントライト
	DirectionLight		mDirectionLight;	// 方向ライト
	SpotLight			mSpotLight;			// スポットライト

	Light();
	virtual ~Light();

	void drawImGui();						// ImGuiでPointLightのデータを出す
	void lightControllerImGui();			// 各ライトの調整ImGui
};

#endif // !_LIGHT_H_