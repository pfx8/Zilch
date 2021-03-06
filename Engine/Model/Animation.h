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
#include "Bone.h"
#include "Node.h"

#include "..\..\Component\Transform.h"

#include "..\Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Animation
{
	friend class Mesh;
	friend class Model;
private:
	void processNode(aiNode* aiNode, const aiScene* scene);		// ノード処理
	HRESULT loadAnimation(wstring const &path);					// アニメーションを読み込み

	void calcInterpolatedScl(D3DXVECTOR3& scl, float animationTime, AnimationChannel* channel);
	void calcInterpolatedRot(D3DXQUATERNION& rot, float animationTime, AnimationChannel* channel);
	void calcInterpolatedPos(D3DXVECTOR3& pos, float animationTime, AnimationChannel* channel);
	unsigned int FindScl(float animationTime, AnimationChannel* channel);
	unsigned int FindRot(float animationTime, AnimationChannel* channel);
	unsigned int FindPos(float animationTime, AnimationChannel* channel);
	void processBoneTransforms(float animationTime, Node<D3DXMATRIX>* node, vector<Bone*>& bones, D3DXMATRIX& parentTransform);	// 時間によって骨の変換行列を計算処理

public:
	float							mLastStartTime = 0.0f;		// 前回アニメーションが終わった時間、最初はゲームスタートので0にする
	float							mDuration;					// アニメーションの続き期間(単位はTicks)
	float							mTicksPerSecond;			// アニメーションの続き期間(Tricks/seconds)
	wstring							mName;						// アニメーションの名前
	vector<AnimationChannel*>		mAnimationChannels;			// すべてのチャンネルデータ
	D3DXMATRIX						mGlobalInverseTransform;	// モデルの空間逆行列
	vector<Node<aiNodeAnim>*>		mNode;						// ノードデータ

	Animation(wstring const &path);
	Animation(aiAnimation* animation);

	~Animation(void);

	void updateBoneTransforms(float timeInSeconds, vector<Bone*>& bones, vector<D3DXMATRIX>& transforms);		// アニメーションキーフレームによって骨の変更行列を更新
};

#endif // !_ANIMATION_H_

