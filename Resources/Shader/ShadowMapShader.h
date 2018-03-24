//*****************************************************************************
//
// �V���h�[�V�F�[�_�[[ShadowMapShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADOW_MAP_SHADER_H_
#define _SHADOW_MAP_SHADER_H_

#include "../Modules/Shader.h"

class ShadowMapShader : public Shader
{
private:
	HRESULT LoadEffectFile();		// ���_�V�F�[�_�[�t�@�C����ǂݍ���

public:
	ID3DXEffect*		effectPoint;				// �G�t�F�N�g(���������_�����O�ۑ������)
	LPDIRECT3DTEXTURE9	shadowMapTex;		// �V���h�[�}�b�v
	D3DXHANDLE			shadeowMapShaderHandle;	// �G�t�F�N�g�̃e�N�j�b�N

	ShadowMapShader();
	~ShadowMapShader();

	HRESULT InitShader();	// �V�F�[�_�[������������
};

#endif // !_SHADOW_MAP_SHADER_H_
