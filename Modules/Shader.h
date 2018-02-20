//*****************************************************************************
//
// �g�D�\���V�F�[�_�[���� [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

#include "../Engine.h"

class Shader
{
private:
	virtual HRESULT LoadEffectFile();					// ���_�V�F�[�_�[�t�@�C����ǂݍ���
	virtual void GetShaderTechniqueAndParameter();		// �V�F�[�_�[���g�����߂ɁA�e�ݒ������

public:
	ID3DXEffect* m_effectPoint;		// �G�t�F�N�g(���������_�����O�ۑ������)
	D3DXHANDLE   m_basicShaderHandle;	// �G�t�F�N�g�̃e�N�j�b�N
	D3DXHANDLE   m_WVPMatrixHandle;	// �ϊ��s��
	//D3DXHANDLE   m_texture1Handle;	// �e�N�X�`��

	Shader();
	~Shader();

	void InitShader();				// �V�F�[�_�[������������
};

#endif // !_SHADER_H_
