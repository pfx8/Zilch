//*****************************************************************************
//
// �r���{�[�h���� [billboard.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "billboard.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
BillBoard::BillBoard()
{
	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->moveSpeedVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->accelerarion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->isUse = true;

	this->titleTexture = NULL;
	this->vertexBuffer = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
BillBoard::~BillBoard()
{
	RELEASE_POINT(this->titleTexture);
	RELEASE_POINT(this->vertexBuffer);
}

//*****************************************************************************
//
// ����������
//
//*****************************************************************************
void BillBoard::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexBillboard();
}

//*****************************************************************************
//
// �X�V����
//
//*****************************************************************************
void BillBoard::Update()
{
	// �����ʒu�̌v�Z 
	this->moveSpeedVec.y += this->accelerarion.y;
	this->pos.y += 0.5f * this->moveSpeedVec.y * ONE_FRAME_TIME;

	// �����ړ�
	this->moveSpeedVec.x += this->accelerarion.x;
	this->moveSpeedVec.z += this->accelerarion.z;
	this->pos.x += this->moveSpeedVec.x;
	this->pos.z += this->moveSpeedVec.z;

	// �n�}�͈̔͂𒴂�����A�e������
	if (this->pos.y <= 0.0f)
	{
		// �������琔�l��S��������
		this->isUse = false;
		this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->moveSpeedVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		// ���_���̍쐬
		MakeVertexBillboard();
	}
}

//*****************************************************************************
//
// �`�揈��
//
//*****************************************************************************
void BillBoard::Draw(D3DXMATRIX viewMatrix)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �r���[�}�g���b�N�X���擾
	mtxView = viewMatrix;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&this->worldMatrix);

	// �|���S���𐳖ʂɌ�����
	this->worldMatrix._11 = mtxView._11;
	this->worldMatrix._21 = mtxView._12;
	this->worldMatrix._12 = mtxView._21;
	this->worldMatrix._31 = mtxView._13;
	this->worldMatrix._13 = mtxView._31;
	this->worldMatrix._22 = mtxView._22;
	this->worldMatrix._32 = mtxView._23;
	this->worldMatrix._23 = mtxView._32;
	this->worldMatrix._33 = mtxView._33;

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, this->scl.x, this->scl.y, this->scl.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &this->worldMatrix);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(BILLBOARDVERTEX));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_BILLBOARDVERTEX);

	// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************************************************************
//
// ���_�쐬
//
//*****************************************************************************
HRESULT BillBoard::MakeVertexBillboard()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(BILLBOARDVERTEX) * 4,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
											D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
											FVF_BILLBOARDVERTEX,		// �g�p���钸�_�t�H�[�}�b�g
											D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
											&this->vertexBuffer,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
											NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		BILLBOARDVERTEX *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		this->vertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].position = pos + D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].position = pos + D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].position = pos + D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].position = pos + D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);

		// �@���̐ݒ�
		pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		this->vertexBuffer->Unlock();
	}

	return S_OK;
}

//*****************************************************************************
//
// ���_���W�̐ݒ�
//
//*****************************************************************************
void BillBoard::SetVertexBillboardByship(float sizeX, float sizeY, Character* ship, bool isLeft)
{
	this->isUse = true;

	this->pos = ship->pos + ship->lookVector * 3.0f;
	this->moveSpeedVec = -ship->lookVector * sizeX;

	if (isLeft == true)
	{
		this->accelerarion = -ship->rightVector * 3;
	}
	else
	{
		this->accelerarion = ship->rightVector * 3;
	}

	// ���W�X�V
	{
		//���_�o�b�t�@�̒��g�𖄂߂�
		BILLBOARDVERTEX *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		this->vertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].position = pos + D3DXVECTOR3(-sizeX / 2, -sizeY / 2, 0.0f);
		pVtx[1].position = pos + D3DXVECTOR3(-sizeX / 2,  sizeY / 2, 0.0f);
		pVtx[2].position = pos + D3DXVECTOR3( sizeX / 2, -sizeY / 2, 0.0f);
		pVtx[3].position = pos + D3DXVECTOR3( sizeX / 2,  sizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		this->vertexBuffer->Unlock();
	}
}