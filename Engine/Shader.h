//*****************************************************************************
//
// �g�D�\���V�F�[�_�[���� [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Engine.h"

class Shader
{
private:

public:
	ID3DXEffect*	effect;		// �G�t�F�N�g

	Shader();
	~Shader();

	HRESULT LoadEffectFile(string shaderName);		// ���_�V�F�[�_�[�t�@�C����ǂݍ���
};

#endif // !_SHADER_H_
