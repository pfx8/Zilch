//*****************************************************************************
//
// Shader���� [Shader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Shader.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Shader::Shader()
{
	m_effectPoint = NULL;
	
	m_WVPMatrixHandle = NULL;
	m_basicShaderHandle = NULL;
	//m_texture1Handle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(m_effectPoint);
}

//*****************************************************************************
//
// �V�F�[�_�[��������
//
//*****************************************************************************
void Shader::InitShader()
{
	// �R���\�[���Ƀ��b�Z�[�W���o��
	std::cout << std::endl << "<Shader>" << std::endl;
	LoadEffectFile();
	GetShaderTechniqueAndParameter();
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT Shader::LoadEffectFile()
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
						"Shader/BasicShader.fx",	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&m_effectPoint,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���


	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] Shader/BasicShader.fx ���ǂݍ��߂Ȃ�" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<BasicShader> Success!" << std::endl;

	return S_OK;
}

//*****************************************************************************
//
// �V�F�[�_�[���g�����߂ɁA�e�ݒ������
//
//*****************************************************************************
void Shader::GetShaderTechniqueAndParameter()
{
	// �����_�����O�̃e�N�j�b�N���擾
	m_basicShaderHandle = m_effectPoint->GetTechniqueByName("BasicShader");	// BasicShader�e�N�j�b�N��ݒ�

	// �V�F�[�_�[���̃O���[�o���ϐ����擾
	m_WVPMatrixHandle = m_effectPoint->GetParameterByName(0, "WVPMatrix");	// WVP�}�g���b�N�X
	//m_texture1Handle = m_effectPoint->GetParameterByName(0, "Tex");			// �e�N�X�`��


}