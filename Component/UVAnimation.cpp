//*****************************************************************************
//
// テクスチャアニメーション処理 [UVAnimation.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "UVAnimation.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
UVAnimation::UVAnimation(D3DXVECTOR2 size, float time)
{
	this->mSize = size;
	this->mTime = time;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
UVAnimation::~UVAnimation()
{

}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void UVAnimation::start()
{
	// 同じgameObjectのアニメーションがやってるモデル
}