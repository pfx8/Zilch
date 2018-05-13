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
enum RenderMode
{
	RT_DIFFUSE,			// �f�B�t���[�Y
	RT_NORMAL,			// �@��
	RT_TEXTURE,			// �e�N�X�`��
	RT_SHADING,			// �V�F�[�f�B���O
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
	RenderMode		mRenderMode;				// �����_�����O���[�h
	ColorRamp		mColorRamp;					// �J���[�����v���[�h
	D3DXVECTOR3		mColorRampSegment;			// �J���[�Z�O�����g�l�A�ő�͂R���x��

	Shader(wstring path);
	~Shader();

	HRESULT loadEffectFile(wstring path);		// ���_�V�F�[�_�[�t�@�C����ǂݍ���
};

#endif // !_SHADER_H_
