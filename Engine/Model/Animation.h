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
	const aiScene*			mAiScene;						// Assimpで読み込んだsceneポインタ
	float					mLastStartTime = 0.0f;			// 前回アニメーションが終わった時間、最初はゲームスタートので0にする
	string					mName;							// アニメーションの名前
	float					mDuration;						// アニメーションの続き時間(単位はTicks)
	float					mTicksPerSecond;					// Tricks/seconds
	unsigned int				mNumChannels;					// 子供ノードのアニメーション数

	void processNode(aiNode* node, const aiScene* scene);			// ノード処理
	HRESULT loadAnimation(string const &path);						// アニメーションを読み込み
	aiNodeAnim* findNodeAnim(aiAnimation* animation, string nodeName);		// 
	void calcInterpolatedScl(aiVector3D& scl, float animationTime, aiNodeAnim* nodeAnim);
	void calcInterpolatedRot(aiQuaternion& rot, float animationTime, aiNodeAnim* nodeAnim);
	void calcInterpolatedPos(aiVector3D& pos, float animationTime, aiNodeAnim* nodeAnim);
	unsigned int FindScl(float animationTime, aiNodeAnim* nodeAnim);
	unsigned int FindRot(float animationTime, aiNodeAnim* nodeAnim);
	unsigned int FindPos(float animationTime, aiNodeAnim* nodeAnim);
	void processAnimationTransforms(float animationTime, const aiNode* node, D3DXMATRIX& parentTransform);	// 時間によって骨の変換行列を計算処理

public:
	vector<AnimationChannel*>		mAnimationChannels;	// すべてのチャンネルデータ

	Animation(string const &path);
	~Animation();

	void processBoneTransforms(float timeInSeconds, vector<D3DXMATRIX>& transforms);		// アニメーション更新
};

#endif // !_ANIMATION_H_

