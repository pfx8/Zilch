//*****************************************************************************
//
// �g�D�\���V�F�[�_�[���� [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CEL_SHADER_H_
#define _CEL_SHADER_H_

#include "../Modules/Shader.h"

class CelShader : public Shader
{
private:
	HRESULT LoadEffectFile();					// ���_�V�F�[�_�[�t�@�C����ǂݍ���
	void GetShaderParameter();		// �V�F�[�_�[���g�����߂ɁA�e�ݒ������

public:
	ID3DXEffect*		effectPoint;		// �G�t�F�N�g(���������_�����O�ۑ������)
	D3DXHANDLE			celShaderHandle;	// �G�t�F�N�g�̃e�N�j�b�N
	D3DXHANDLE			WMatrixHandle;	// ���[���h�ϊ�
	D3DXHANDLE			VPMatrixHandle;	// �r���[�C���O�ϊ��ƃv���W�F�N�V�����ϊ�
	D3DXHANDLE			lightingHandle;	// ���̕���
	D3DXHANDLE			typeHandle;		// �I�u�W�F�N�g�̎�ނ𔻒f

	CelShader();
	~CelShader();

	void InitShader();						// �V�F�[�_�[������������
};

#endif // !_CEL_SHADER_H_
