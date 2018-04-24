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
#include "../Engine/Engine.h"

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

class Light : public Component
{
private:

public:
	D3DXVECTOR3			mLightPos;				// 太陽の位置
	//D3DXVECTOR3			mLightDirection;		// ライトの方向
	D3DXVECTOR4			mLightColor;			// ライトのカラー
	PointLight			mPointLight;			// ポイントライトのプロパティ

	Light();
	virtual ~Light();
};

#endif // !_LIGHT_H_
