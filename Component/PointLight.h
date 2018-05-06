//*****************************************************************************
//
// ポイントライト処理 [PointLight.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "Component.h"
#include "../Engine/Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class PointLight : public Component
{
private:

public:
	// ポイントライト減衰公式
	// Luminosity = 1 / Attenuation
	// Attenuation = Constant + Linear * Distance + Quadratic * Distance ^ 2
	// http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation

	// 明度 = 1 / 減衰値
	// 減衰値 = 1.0/(constant + linear * d + quadratic * d^2)
	float				mConstant;			// 定数、いつも1.0で
	float				mLinear;			// リニア的で強度を減少させる
	float				mQuadratic;			// 二次で強度を減少させる

	D3DXVECTOR3			mLightPos;			// ライトの位置
	D3DXVECTOR4			mLightColor;		// ライトのカラー

	PointLight();
	virtual ~PointLight();

	void drawImGui();						// ImGuiでPointLightのデータを出す
};

#endif // !_PONIT_LIGHT_H_