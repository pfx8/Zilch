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
	unsigned int				index;								//	����ID
	D3DXMATRIX				nodeTransform;				// 
	D3DXMATRIX				offset;								// 
	
	// �A�j���[�V�������
	D3DXMATRIX				lastTransform;				// �Ō�v�Z�ł����s��
	D3DXVECTOR3			scl;									// �g��k��
	D3DXVECTOR3			rot;									// �p�x�̕ύX

	Bone();
	Bone(unsigned int index, D3DXMATRIX offset);
	~Bone();
};

#endif // !_BONE_H_

