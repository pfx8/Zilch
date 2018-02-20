//*****************************************************************************
//
// ���f������ [Model.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

#include "Material.h"
#include "..\Engine.h"
#include "..\Shader\CelShader.h"


//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Model
{
private:
	D3DXMATRIX		worldMatrix;	// ���[���h�ϊ��}�g���b�N�X

	void SetWorldMatrix();						// ���[���h�ϊ�
	void RotationVecUp(float angle);			// ������̃x�N�g���ɂ��ĉ�]

public:
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		rot;			// ��]
	D3DXVECTOR3		scl;			// �g��k��
	D3DXVECTOR3		upVector;		// �J�����̏�����x�N�g��
	D3DXVECTOR3		lookVector;		// �J�����̒��������x�N�g��
	D3DXVECTOR3		rightVector;	// �J�����̉E�����x�N�g��

	LPD3DXMESH						meshPoint;			// ���b�V�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9				meshTexturePoint;	// �e�N�X�`���}�l�W�����g
	Material*						material;			// �}�e���A�����ւ̃|�C���^
	IDirect3DVertexDeclaration9*	vertexDecl;			// ���_�錾

	Model();
	~Model();

	void Update();	// �X�V
	void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);	// ���f����`�悷��
};

#endif // !_MODEL_H_

