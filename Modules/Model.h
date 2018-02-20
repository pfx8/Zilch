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

enum Model_Type
{
	MT_ship = 0,
	MT_bullet,
};

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Model
{
private:

public:
	LPD3DXMESH						meshPoint;			// ���b�V�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9				meshTexturePoint;	// �e�N�X�`���}�l�W�����g
	Material*						material;			// �}�e���A�����ւ̃|�C���^
	IDirect3DVertexDeclaration9*	vertexDecl;			// ���_�錾

	Model();
	~Model();

	void DrawModel(CelShader* celShader, D3DXMATRIX* worldMatrix, D3DXMATRIX* VPMatrix,
		D3DXMATRIX* lightMatrix, D3DXMATRIX* normalMatrix, Model_Type modelType);	// ���f����`�悷��
};

#endif // !_MODEL_H_

