//*****************************************************************************
//
// アニメーションチャンネル処理 [AnimationChannel.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _ANIMATION_CHANNEL_H_
#define _ANIMATION_CHANNEL_H_

#include "Engine\Engine.h"

//*****************************************************************************
//
// 構造体定義
//
//*****************************************************************************
struct VertexKey
{
	float				time;			// 今のフレーム
	D3DXVECTOR3			value;			// 今のフレームの頂点座標
};

struct QuaternionKey
{
	float				time;			// 今のフレーム
	D3DXQUATERNION		value;			// 回転情報を四元数に入れる
};
//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class AnimationChannel
{
private:

public:
	string						mBoneName;				// 骨の名前
	vector<VertexKey>			mPosKeys;				// 頂点座標
	vector<QuaternionKey>		mRotkeys;				// 回転四元数
	vector<VertexKey>			mSclKeys;				// 拡大縮小データ

	AnimationChannel();
	~AnimationChannel();
};

#endif // !_ANIMATION_CHANNEL_H_

