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
Shader::Shader(string path)
{
	string name = path.substr(path.find_last_of("//") + 1, path.find_last_of("/n"));
	cout << "<Shader> : "  << name;
	loadEffectFile(path);

	// �f�t�H���g�V�F�[�f�B���O���[�h��ݒ�
	this->mRenderType = RT_TEXTURE;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(mEffect);
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT Shader::loadEffectFile(string path)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	D3DCAPS9 caps;
	pD3DDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))	// �s�N�Z���@�\�`�F�b�N
	{
		cout << "[Error] Don't support pixel shader!" << endl;
	}

	ID3DXBuffer* errorBuffer = nullptr	;		// �G���[�o�b�t�@
	D3DXCreateEffectFromFile(pD3DDevice,
						path.c_str(),	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->mEffect,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���

	if (errorBuffer)	// �G���[���`�F�b�N
	{
		cout << "[Error] Loading <Shader> " << path  << " ... fail!" << endl;	// �G���[���b�Z�[�W
		cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	cout << " loading ... success!" << endl;

	return S_OK;
}