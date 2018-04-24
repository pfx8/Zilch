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

class Light : public Component
{
private:

public:
	D3DXVECTOR3			mPosition;				// 太陽の位置
	D3DXVECTOR3			mLightDirection;		// ライトの方向
	D3DXVECTOR4			mLightColor;			// ライトのカラー



	Light();
	virtual ~Light();
};

#endif // !_LIGHT_H_
