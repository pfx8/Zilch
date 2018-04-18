//*****************************************************************************
//
// �A�j���[�V�������� [Animation.h]
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
// �N���X�錾
//
//*****************************************************************************
class Animation
{
	friend class Mesh;
private:
	const aiScene*			mAiScene;						// Assimp�œǂݍ���scene�|�C���^
	float					mLastStartTime = 0.0f;			// �O��A�j���[�V�������I��������ԁA�ŏ��̓Q�[���X�^�[�g�̂�0�ɂ���
	string					mName;							// �A�j���[�V�����̖��O
	float					mDuration;						// �A�j���[�V�����̑�������(�P�ʂ�Ticks)
	float					mTicksPerSecond;					// Tricks/seconds
	unsigned int				mNumChannels;					// �q���m�[�h�̃A�j���[�V������

	void processNode(aiNode* node, const aiScene* scene);			// �m�[�h����
	HRESULT loadAnimation(string const &path);						// �A�j���[�V������ǂݍ���
	aiNodeAnim* findNodeAnim(aiAnimation* animation, string nodeName);		// 
	void calcInterpolatedScl(aiVector3D& scl, float animationTime, aiNodeAnim* nodeAnim);
	void calcInterpolatedRot(aiQuaternion& rot, float animationTime, aiNodeAnim* nodeAnim);
	void calcInterpolatedPos(aiVector3D& pos, float animationTime, aiNodeAnim* nodeAnim);
	unsigned int FindScl(float animationTime, aiNodeAnim* nodeAnim);
	unsigned int FindRot(float animationTime, aiNodeAnim* nodeAnim);
	unsigned int FindPos(float animationTime, aiNodeAnim* nodeAnim);
	void processAnimationTransforms(float animationTime, const aiNode* node, D3DXMATRIX& parentTransform);	// ���Ԃɂ���č��̕ϊ��s����v�Z����

public:
	vector<AnimationChannel*>		mAnimationChannels;	// ���ׂẴ`�����l���f�[�^

	Animation(string const &path);
	~Animation();

	void processBoneTransforms(float timeInSeconds, vector<D3DXMATRIX>& transforms);		// �A�j���[�V�����X�V
};

#endif // !_ANIMATION_H_

