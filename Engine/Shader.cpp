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
	// �p�X����t�@�C���̖��O���擾(�g���q����)
	string name1 = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	string name2 = name1.substr(0, name1.find_first_of("."));							// exp: ccc.fbx -> ccc

	loadEffectFile(path);

	// �f�t�H���g�V�F�[�f�B���O���[�h��ݒ�
	this->mRenderMode = RT_TEXTURE;

	// �J���[�����v���[�h��ݒ�
	this->mColorRamp = CR_LINEAR;

	// �Z�O�����g��ݒ�
	this->mColorRampSegment = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		// Debug�E�C���h��
		cout << "<Error> don't support pixel shader!" << endl;
	}

	ID3DXBuffer* errorBuffer = nullptr;		// �G���[�o�b�t�@
	D3DXCreateEffectFromFile(pD3DDevice,
						path.c_str(),		// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->mEffect,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���

	if (errorBuffer)	// �G���[���`�F�b�N
	{
		// Debug�E�C���h��
		cout << "<Error> loading " << path  << " ... fail!" << endl;	// �G���[���b�Z�[�W
		cout << "<Information> " << (char*)errorBuffer->GetBufferPointer() << endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	// Debug�E�C���h��
	cout << "<Scene> loading " << path << " ... success!" << endl;

	return S_OK;
}