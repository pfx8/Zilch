//*****************************************************************************
//
// Shader���� [Shader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Engine.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Shader::Shader()
{
	this->effect = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(this->effect);
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT Shader::LoadEffectFile(std::string effectFileName)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))	// �s�N�Z���@�\�`�F�b�N
	{
		std::cout << "[Error] Don't support pixel shader!" << std::endl;
	}

	ID3DXBuffer* errorBuffer = NULL;		// �G���[�o�b�t�@
	D3DXCreateEffectFromFile(pDevice,
						effectFileName.c_str(),	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->effect,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���

	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] Loading <Shader> " << effectFileName  << " ... Fail!" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading <Shader> " << effectFileName << " ... Success!" << std::endl;

	return S_OK;
}