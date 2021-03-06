﻿//*****************************************************************************
//
// アニメーションチャンネル処理 [AnimationChannels.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "AnimationChannel.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
AnimationChannel::AnimationChannel(void)
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
AnimationChannel::~AnimationChannel(void)
{
	// コンテナをリリーズ
	vector<VertexKey>().swap(this->mPosKeys);
	vector<QuaternionKey>().swap(this->mRotkeys);
	vector<VertexKey>().swap(this->mSclKeys);
}