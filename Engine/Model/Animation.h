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
#include "Bone.h"
#include "Node.h"
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
	float					mLastStartTime = 0.0f;			// �O��A�j���[�V�������I��������ԁA�ŏ��̓Q�[���X�^�[�g�̂�0�ɂ���
	string					mName;							// �A�j���[�V�����̖��O
	float					mDuration;						// �A�j���[�V�����̑�������(�P�ʂ�Ticks)
	float					mTicksPerSecond;				// Tricks/seconds

	void processNode(Node* node, aiNode* aiNode, const aiScene* scene);			// �m�[�h����
	HRESULT loadAnimation(string const &path);						// �A�j���[�V������ǂݍ���

	void calcInterpolatedScl(D3DXVECTOR3& scl, float animationTime, AnimationChannel* channel);
	void calcInterpolatedRot(D3DXQUATERNION& rot, float animationTime, AnimationChannel* channel);
	void calcInterpolatedPos(D3DXVECTOR3& pos, float animationTime, AnimationChannel* channel);
	unsigned int FindScl(float animationTime, AnimationChannel* channel);
	unsigned int FindRot(float animationTime, AnimationChannel* channel);
	unsigned int FindPos(float animationTime, AnimationChannel* channel);
	void processBoneTransforms(float animationTime, Node* node, vector<Bone*>& bones, D3DXMATRIX& parentTransform);	// ���Ԃɂ���č��̕ϊ��s����v�Z����

public:
	vector<AnimationChannel*>		mAnimationChannels;			// ���ׂẴ`�����l���f�[�^
	D3DXMATRIX						mGlobalInverseTransform;	// ���f���̋�ԋt�s��
	vector<Node*>					mNode;						// �m�[�h�f�[�^

	Animation(string const &path);
	~Animation();

	void updateBoneTransforms(float timeInSeconds, vector<Bone*>& bones, vector<D3DXMATRIX>& transforms);		// �A�j���[�V�����L�[�t���[���ɂ���č��̕ύX�s����X�V
	void traverseBoneNode(Node* node, unsigned int level);	// ���m�[�h���g���o�[�X
};

#endif // !_ANIMATION_H_

