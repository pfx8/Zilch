//*****************************************************************************
//
// フラッシュライト処理 [FlashLight.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _FLASH_LIGHT_H_
#define _FLASH_LIGHT_H_

#include "Component.h"
#include "../Engine/Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class FlashLight : public Component
{
private:

public:
	D3DXVECTOR3			mLightPos;				// 太陽の位置
	D3DXVECTOR3			mLightDirection;		// ライトの方向
	D3DXVECTOR4			mLightColor;			// ライトのカラー
	float				mCutOff;				// ライト角度の範囲(Radianで計算)

	FlashLight();
	virtual ~FlashLight();
};

#endif // !_LIGHT_H_
