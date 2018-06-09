//*****************************************************************************
//
// �V���h�E�}�b�v����[ShadowMap.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ShadowMap.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
ShadowMap::ShadowMap(Shader* shader, D3DXVECTOR3 lightPos)
{
	// �e������
	this->mShader = shader;
	this->mLightPos = mLightPos;
	this->mLightAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->mLightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	HRESULT result;
	// �V���h�E�}�b�v�e�N�X�`�������
	result = D3DXCreateTexture(getD3DDevice(), this->mMapSize, this->mMapSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &this->mShadowMap);
	//�V���h�E�}�b�v�[�x�o�b�t�@�T�[�t�F�C�X�����
	result = getD3DDevice()->CreateDepthStencilSurface(this->mMapSize, this->mMapSize, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &this->mShadowMapDepth, NULL);
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
ShadowMap::~ShadowMap()
{
	RELEASE_POINT(this->mShadowMap);
	RELEASE_POINT(this->mShadowMapDepth);
}

//*****************************************************************************
//
// �V���h�E�}�b�v�X�V
//
//*****************************************************************************
void ShadowMap::update()
{
	// ���C�g�ɂ��̃r���[�C���O�ϊ�
	D3DXMatrixLookAtLH(&this->mLightView, &this->mLightPos, &this->mLightAt, &this->mLightUp);

	// �v���W�F�N�V�����ϊ�
	D3DXMatrixPerspectiveFovLH(&this->mLightProjection, D3DXToRadian(45), 1.0f, 1.0f, 1024.0f);

	// �V���h�E�}�b�v�pWVP�v�Z
	this->mShadowWVP = this->mTargetWVP * this->mLightView * this->mLightProjection;
}

//*****************************************************************************
//
// �V���h�E�}�b�v��`��
//
//*****************************************************************************
void ShadowMap::draw(Model* model)
{
	// �V���h�E�}�b�v�̃T�[�t�F�C�X���擾
	LPDIRECT3DSURFACE9 renderTarget;
	this->mShadowMap->GetSurfaceLevel(0, &renderTarget);

	// �O�̃����_�����O�^�[�Q�b�g��ۑ�
	LPDIRECT3DSURFACE9 oldRenderTarget;
	getD3DDevice()->GetRenderTarget(0, &oldRenderTarget);
	// �V���h�E�}�b�v��V���������_�����O�^�[�Q�b�g�ɐݒ�
	getD3DDevice()->SetRenderTarget(0, renderTarget);

	// �[�x�o�b�t�@������
	LPDIRECT3DSURFACE9 oldDepth;
	getD3DDevice()->GetDepthStencilSurface(&oldDepth);
	getD3DDevice()->SetDepthStencilSurface(this->mShadowMapDepth);

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	getD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 0, 0), 1.0f, 0);

	// �V���h�E�}�b�v��`��
	this->mShader->mEffect->SetMatrix("worldViewProjectionShadow", &this->mShadowWVP);
	model->drawShadow(this->mShader);

	// �ۑ��V���h�E�}�b�v
	if (GetKeyboardTrigger(DIK_F6))			// key F6
	{
		D3DXSaveTextureToFile(L"shadowMap.jpg", D3DXIFF_JPG, this->mShadowMap, NULL);
	}

	// �V���h�E�}�b�v�������ŁA���̃����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@�ɖ߂�
	getD3DDevice()->SetRenderTarget(0, oldRenderTarget);
	getD3DDevice()->SetDepthStencilSurface(oldDepth);

	// �����[�X�V���h�E�}�b�v�Ɋւ���|�C���^
	RELEASE_POINT(oldRenderTarget);
	RELEASE_POINT(oldDepth);
	RELEASE_POINT(renderTarget);
}