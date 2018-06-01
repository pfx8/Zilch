//*****************************************************************************
//
// �X�J�C�{�b�N�X���� [SkyBox.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "Engine.h"
#include "Shader.h"

//*****************************************************************************
//
// ���_�݌v
//
//*****************************************************************************
typedef struct SKYBOXVERTEX
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR2 uv;		// UV���W
}SKYBOXVERTEX;

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SkyBox
{
private:
	D3DXVECTOR3						pos;			// ���W
	IDirect3DVertexDeclaration9*	vertexDecl;		// ���_�V�F�[�_�[�錾
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			indexBuffer;	// �C���f�b�N�X�o�b�t�@
	float							length;		// �{�b�N�X�̒���

public:
	D3DXMATRIX						wMatrix;	// ���[���h�ϊ��}�g���b�N�X
	LPDIRECT3DTEXTURE9				tex;		// �e�N�X�`���z��
	
	SkyBox(void);
	~SkyBox(void);

	HRESULT InitSkyBox(float length);		// �X�J�C�{�b�N�X��������
	void SetWorldMatrix(void);					// ���[���h�ϊ�
	void draw(Shader* mShader, D3DXMATRIX* vMatrix, D3DXMATRIX* pMatrix);	// �X�J�C�{�b�N�X��`��
};

#endif // !_SKY_BOX_H_