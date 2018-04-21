//*****************************************************************************
//
// 方向ライト処理 [DirectionalLight.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "Component.h"
#include "../Engine/Engine.h"

class DirectionalLight : public Component
{
private:

public:
	D3DXVECTOR3			mSunPos;				// 太陽の位置
	D3DXVECTOR3			mLightDirection;		// ライトの方向
	D3DXVECTOR4			mLightColor;			// ライトのカラー

	DirectionalLight();
	virtual ~DirectionalLight();
};

#endif // !_DIRECTIONAL_LIGHT_H_
