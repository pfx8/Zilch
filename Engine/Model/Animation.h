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
	const aiScene	*			mAiScene;													// Assimpで読み込んだsceneポインタ
	float							mLastStartTime = 0.0f;								// 最後にアニメーションがスタートした時間、最初はゲームスタートので0にする
	string							mName;														// アニメーションの名前
	float							mDuration;													// アニメーションの続き時間(単位はfps)
	float							mTicksPerSecond;										// fps/seconds
	unsigned int				mNumChannels;										// 子供ノードのアニメーション数

	void processNode(aiNode* node, const aiScene* scene);			// ノード処理
	HRESULT loadAnimation(string const &path);							// アニメーションを読み込み
	void processAnimationUpdate(float animationTime, const aiNode* node, D3DXMATRIX& parentTransform);							// 時間によって骨の変換行列を計算処理

public:
	vector<AnimationChannel*>				mAnimationChannels;	// すべてのチャンネルデータ

	Animation(string const &path);
	~Animation();

	void processBoneTransform(vector<D3DXMATRIX>& matrixs, float timeInSeconds);							// アニメーション更新
};

#endif // !_ANIMATION_H_

