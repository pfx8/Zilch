//*****************************************************************************
//
// アニメーション処理 [Animation.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "AnimationChannel.h"
#include "../Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Animation
{
	friend class Mesh;
private:
	string							mName;														// アニメーションの名前
	float							mDuration;													// アニメーションの続き時間(単位はfps)
	float							mTicksPerSecond;										// fps/seconds
	unsigned int				mNumChannels;										// 子供ノードのアニメーション数

	void processNode(aiNode *node, const aiScene *scene);			// ノード処理
	HRESULT loadAnimation(string const &path);							// アニメーションを読み込み

public:

	Animation(string const &path);
	~Animation();
};

#endif // !_ANIMATION_H_

