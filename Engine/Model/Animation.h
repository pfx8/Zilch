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
	const aiScene	*			mAiScene;													// Assimp�œǂݍ���scene�|�C���^
	float							mLastStartTime = 0.0f;								// �Ō�ɃA�j���[�V�������X�^�[�g�������ԁA�ŏ��̓Q�[���X�^�[�g�̂�0�ɂ���
	string							mName;														// �A�j���[�V�����̖��O
	float							mDuration;													// �A�j���[�V�����̑�������(�P�ʂ�fps)
	float							mTicksPerSecond;										// fps/seconds
	unsigned int				mNumChannels;										// �q���m�[�h�̃A�j���[�V������

	void processNode(aiNode* node, const aiScene* scene);			// �m�[�h����
	HRESULT loadAnimation(string const &path);							// �A�j���[�V������ǂݍ���
	void processAnimationUpdate(float animationTime, const aiNode* node, D3DXMATRIX& parentTransform);							// ���Ԃɂ���č��̕ϊ��s����v�Z����

public:
	vector<AnimationChannel*>				mAnimationChannels;	// ���ׂẴ`�����l���f�[�^

	Animation(string const &path);
	~Animation();

	void processBoneTransform(vector<D3DXMATRIX>& matrixs, float timeInSeconds);							// �A�j���[�V�����X�V
};

#endif // !_ANIMATION_H_

