//*****************************************************************************
//
// ������ [Bone.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BONE_H_
#define _BONE_H_

#include "../Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Bone
{
	friend class Mesh;
private:

public:
	// �����
	unsigned int					mIndex;								// ���̔ԍ�
	D3DXMATRIX					mNodeTransform;				// 
	D3DXMATRIX					mOffset;								// ���f���̃��[�g�ɑ΂��ĕύX�s��
	
	// �A�j���[�V�������
	D3DXMATRIX					mFinaTransform;				// ���ׂĂ̐e�s����v�Z�����ŏI�s��
	D3DXVECTOR3				mScl;									// �g��k��
	D3DXVECTOR3				mSot;									// �p�x�̕ύX

	Bone();
	Bone(unsigned int index, D3DXMATRIX offset);
	~Bone();
};

#endif // !_BONE_H_

