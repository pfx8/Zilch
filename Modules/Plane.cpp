//*****************************************************************************
//
// ���ʏ���[Plane.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Plane.h"

#include "../ResourcesManager.h"
//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Plane::Plane()
{

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->vertexBuffer = NULL;
	this->indexBuffer = NULL;
	this->tex = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Plane::~Plane()
{
	// �|�C���^
	RELEASE_POINT(this->vertexBuffer);
	RELEASE_POINT(this->indexBuffer);
	RELEASE_POINT(this->tex);
}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
HRESULT Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	this->pos = pos;	// �ʒu
	this->planeNum = planeNum;
	this->planeSize = planeSize;

	MakeVertexDecl(this->planeSize, this->planeNum);	// ���_�錾(shader)

	return S_OK;
}

//*****************************************************************************
//
// ���_�錾(Shader)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	this->vertexNum = (planeNum.x + 1) * (planeNum.y + 1);	// �����_��
	this->polygonNum = planeNum.x * planeNum.y * 2 + (planeNum.y - 1) * 4;		// �|���S����
	this->indexNum = (planeNum.x + 1) * 2 * planeNum.y + (planeNum.y - 1) * 2;	// �C���f�b�N�X��

	// ���_�V�F�[�_�[�錾
	{
		D3DVERTEXELEMENT9 planeDecl[] =		// ���_�f�[�^�̃��C�A�E�g���`
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(planeDecl, &this->vertexDecl);
	}

	// ���_�o�b�t�@�쐬
	{
		if (FAILED(pDevice->CreateVertexBuffer(this->vertexNum * sizeof(PLANEVERTEX), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &this->vertexBuffer, NULL)))
		{
			std::cout << "[Error] Make <Plane> vertex buffer ... Fail!" << std::endl;	// �G���[���b�Z�[�W
			return E_FAIL;
		}

		PLANEVERTEX* VertexBuffer;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾����
		this->vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

		// ���_�o�b�t�@�̒��g�𖄂߂�
		// ���_���W(���[�J�����W = �`���`�����Ă�)
		// ���̎��g�̍��W�A���E�ł̍��W�ɂ͊֌W�Ȃ�
		// this->posFiled�͐��E�ł̈ʒu��

		for (int numY = 0; numY < (planeNum.y + 1); numY++)
		{
			for (int numX = 0; numX < (planeNum.x + 1); numX++)
			{
				// ���_���W�̐ݒ�
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.x = -(planeNum.x / 2.0f) * planeSize.x + numX * planeSize.x;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.y = 0;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.z = (planeNum.y / 2.0f) * planeSize.y - numY * planeSize.y;
				//�@���̐ݒ�
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// �e�N�X�`�����W�̐ݒ�
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texture.x = numX * 1.0f;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texture.y = numY * 1.0f;
			}
		}

		// ���_�f�[�^���A�����b�N����
		this->vertexBuffer->Unlock();
	}

	// ���_�C���f�b�N�X�o�b�t�@�쐬
	{
		if (FAILED(pDevice->CreateIndexBuffer(this->indexNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->indexBuffer, NULL)))
		{
			std::cout << "[Error] Make <Plane> vertex index buffer ... Fail!" << std::endl;	// �G���[���b�Z�[�W
			return E_FAIL;
		}

		WORD* vertexIndex = NULL;		// �C�f�b�N�X�̒��g�𖄂߂�

		this->indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// �C���f�b�N�X �f�[�^�̂�����͈͂����b�N���A���̃C���f�b�N�X �o�b�t�@�[ �������[�ւ̃|�C���^�[���擾����

		int index = 0;
		for (int numY = 0; numY < planeNum.y; numY++)
		{
			if (numY > 0)
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				vertexIndex[index] = (numY + 1) * (planeNum.x + 1);
				index++;
			}

			for (int nCntVtxX = 0; nCntVtxX < (planeNum.x + 1); nCntVtxX++)
			{
				vertexIndex[index] = (numY + 1) * (planeNum.x + 1) + nCntVtxX;
				index++;
				vertexIndex[index] = numY * (planeNum.x + 1) + nCntVtxX;
				index++;
			}

			if (numY < (planeNum.y - 1))
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				vertexIndex[index] = numY * (planeNum.x + 1) + planeNum.x;
				index++;
			}
		}

		this->indexBuffer->Unlock();	// �C���f�b�N�X �f�[�^�̃��b�N����������
	}

	return S_OK;
}

//*****************************************************************************
//
// �X�V
//
//*****************************************************************************
void Plane::Update()
{
	// �s��X�V
	SetWorldMatrix();

	if (GetKeyboardTrigger(DIK_F1))
	{
		renderStatus = RS_withoutLight;
	}
	if (GetKeyboardTrigger(DIK_F2))
	{
		renderStatus = RS_withLight;
	}
}

//*****************************************************************************
//
// ���[���h�ϊ�
//
//*****************************************************************************
void Plane::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(&this->wMatrix);

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->wMatrix, &this->wMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// �e�N�X�`����`�悷��
//
//*****************************************************************************
void Plane::Draw(Shader* shader2D, Camera* camera)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�j�b�N��ݒ�
	switch (renderStatus)
	{
	case RS_withoutLight:
		shader2D->effect->SetTechnique("render_without_light");
		break;
	case RS_withLight:
		shader2D->effect->SetTechnique("render_with_light");

		// �J�����ʒu�̐ݒ�
		shader2D->effect->SetValue("cameraPos", &camera->posEye, sizeof(D3DXVECTOR3));
		break;
	case RS_withNormalMap:
		break;
	}

	// ���[���h�ϊ��A�r���[�C���O�ϊ��A�v���W�F�N�V�����ϊ��}�g���b�N�X
	shader2D->effect->SetMatrix("wMat", &this->wMatrix);
	shader2D->effect->SetMatrix("vMat", &camera->vMatrix);
	shader2D->effect->SetMatrix("pMat", &camera->pMatrix);

	// �e�N�X�`���̐ݒ�
	shader2D->effect->SetTexture("tex", this->tex);

	// �`��
	UINT passNum = 0;
	shader2D->effect->Begin(&passNum, 0);
	// �e�p�X�����s����
	for (int count = 0; count < passNum; count++)
	{
		shader2D->effect->BeginPass(count);
		
		pDevice->SetVertexDeclaration(this->vertexDecl);							// ���_�錾��ݒ�
		pDevice->SetStreamSource(0, this->vertexBuffer, 0, sizeof(PLANEVERTEX));	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C�i��
		pDevice->SetIndices(this->indexBuffer);										// ���_�C���f�b�N�X�o�b�t�@��ݒ�
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, this->vertexNum, 0, this->polygonNum);	// �|���S���̕`��

		shader2D->effect->EndPass();
	}
	shader2D->effect->End();
}