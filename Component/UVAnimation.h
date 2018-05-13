//*****************************************************************************
//
// テクスチャアニメーション処理 [UVAnimation.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _UVANIMATION_H_
#define _UVANIMATION_H_

#include "Component.h"

#include "Engine\Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class UVAnimation : public Component
{
private:
	void start();

public:
	D3DXVECTOR2		mSize;		// テクスチャのサイズ
	float			mTime;		// アニメーションの時間

	UVAnimation(D3DXVECTOR2 size, float time);
	~UVAnimation();
};

#endif // !_UVANIMATION_H_
