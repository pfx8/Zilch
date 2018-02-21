//*****************************************************************************
//
// �V���h�[�V�F�[�_�[[ShadowMapShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ShadowMapShader.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
ShadowMapShader::ShadowMapShader()
{
	this->effectPoint = NULL;
	this->shadowMapTex = NULL;
	this->shadeowMapShaderHandle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
ShadowMapShader::~ShadowMapShader()
{
	RELEASE_POINT(this->effectPoint);
}

//*****************************************************************************
//
// �V�F�[�_�[��������
//
//*****************************************************************************
HRESULT ShadowMapShader::InitShader()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadEffectFile();

	if (FAILED(pDevice->CreateTexture(512, 512,
		1, D3DUSAGE_RENDERTARGET,
		D3DFMT_R32F,
		D3DPOOL_DEFAULT,
		&this->shadowMapTex,
		NULL)))
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
		return E_FAIL;
	}
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT ShadowMapShader::LoadEffectFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))	// �s�N�Z���@�\�`�F�b�N
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
	}

	ID3DXBuffer* errorBuffer = NULL;		// �G���[�o�b�t�@
	D3DXCreateEffectFromFile(pDevice,
						"Shader/ShadowMapShader.fx",	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->effectPoint,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���


	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] Shader/ShadowMapShader.fx ���ǂݍ��߂Ȃ�" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<ShadowMapShader> Success!" << std::endl;

	return S_OK;
}