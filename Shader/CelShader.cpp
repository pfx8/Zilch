//*****************************************************************************
//
// �g�D�\���V�F�[�_�[���� [CelShader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "CelShader.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
CelShader::CelShader()
{
	this->effectPoint = NULL;
	this->celShaderHandle = NULL;
	this->WMatrixHandle = NULL;
	this->VPMatrixHandle = NULL;
	this->lightingHandle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
CelShader::~CelShader()
{
	RELEASE_POINT(this->effectPoint);
}

//*****************************************************************************
//
// �V�F�[�_�[��������
//
//*****************************************************************************
void CelShader::InitShader()
{
	LoadEffectFile();
	GetShaderParameter();
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT CelShader::LoadEffectFile()
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
						"Shader/CelShader.fx",	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->effectPoint,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���


	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] Shader/CelShader.fx ���ǂݍ��߂Ȃ�" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<CelShader> Success!" << std::endl;
	return S_OK;
}

//*****************************************************************************
//
// �V�F�[�_�[���g�����߂ɁA�e�ݒ������
//
//*****************************************************************************
void CelShader::GetShaderParameter()
{
	// �����_�����O�̃e�N�j�b�N���擾
	this->celShaderHandle = this->effectPoint->GetTechniqueByName("CelShader");

	// �V�F�[�_�[���̃O���[�o���ϐ����擾
	this->WMatrixHandle = this->effectPoint->GetParameterByName(0, "WMatrix");
	this->VPMatrixHandle = this->effectPoint->GetParameterByName(0, "VPMatrix");
	this->typeHandle = this->effectPoint->GetParameterByName(0, "ObjType");
}