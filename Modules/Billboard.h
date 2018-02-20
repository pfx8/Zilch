//*****************************************************************************
//
// �r���{�[�h���� [billboard.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BILLBOARD_H_
#define  _BILLBOARD_H_

#include "../Engine.h"
#include "Character.h"

#define	BILLBOARD_SIZE_X		(10.0f)							// �r���{�[�h�̕�
#define	BILLBOARD_SIZE_Y		(10.0f)							// �r���{�[�h�̍���

typedef struct BILLBOARDVERTEX
{
	D3DXVECTOR3 position;		// ���_���W
	D3DXVECTOR3 normal;			// �@��
	D3DCOLOR	diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;			// �e�N�X�`�����W
}BILLBOARDVERTEX;

#define	FVF_BILLBOARDVERTEX	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class BillBoard
{
private:
	HRESULT MakeVertexBillboard();	// ���_�쐬

public:
	LPDIRECT3DTEXTURE9		titleTexture;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;				// ���_�o�b�t�@

	D3DXMATRIX				worldMatrix;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3				pos;						// �ʒu
	D3DXVECTOR3				scl;						// �X�P�[��

	D3DXVECTOR3				moveSpeedVec;				// �ړ���
	D3DXVECTOR3				accelerarion;				// ���������x

	bool					isUse;

	BillBoard();
	~BillBoard();

	void Init();
	void Update();
	void Draw(D3DXMATRIX viewMatrix);
	void SetVertexBillboardByship(float sizeX, float sizeY, Character* ship, bool isLeft);	// ���_���W��ݒ�
};
#endif // !_BILLBOARD_H_






