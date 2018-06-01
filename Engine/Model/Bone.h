//*****************************************************************************
//
// ������ [Bone.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BONE_H_
#define _BONE_H_

#include "..\Engine.h"

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
	string					mName;						// ���̖��O
	unsigned int			mIndex;						// �����g�̔ԍ�
	D3DXMATRIX				mNodeTransform;				// �Ή����ăm�[�h�̔ԍ�
	D3DXMATRIX				mOffset;					// ���f���̃��[�g�ɑ΂��ĕύX�s��
	
	// �A�j���[�V�������
	D3DXMATRIX				mFinaTransform;				// ���ׂĂ̐e�s����v�Z�����ŏI�s��
	D3DXVECTOR3				mScl;						// �g��k��
	D3DXVECTOR3				mSot;						// �p�x�̕ύX

	Bone(void);
	Bone(unsigned int index, D3DXMATRIX offset, string name);
	~Bone(void);
};

#endif // !_BONE_H_

