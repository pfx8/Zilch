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

//*****************************************************************************
//
//  �񋓑̒�`
//
//*****************************************************************************
enum RenderingMode
{
	RM_TEXTURE,			// �e�N�X�`��
	RM_DIFFUSE,			// �f�B�t���[�Y
	RM_SPECULAR,		// �X�y�L�����[
	RM_NORMAL,			// �@��
	RM_SHADING,			// �V�F�[�f�B���O
};

enum ColorRamp
{
	CR_LINEAR,			// ���j�A
	CR_CONSTANT,		// ���
};

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Shader
{
private:

public:
	ID3DXEffect*	mEffect;					// �G�t�F�N�g
	RenderingMode	mRenderingMode;				// �����_�����O���[�h
	ColorRamp		mColorRampType;				// �J���[�����v���[�h
	D3DXVECTOR3		mColorRampSegment;			// �J���[�Z�O�����g�l�A�ő�͂R���x��
	float			mSpecularColorSegment;		// �X�y�L�����[�Z�O�����g�l�A0.0 ~ 1.0

	Shader(wstring path);
	~Shader(void);

	HRESULT loadEffectFile(wstring path);		// ���_�V�F�[�_�[�t�@�C����ǂݍ���
};

#endif // !_SHADER_H_
