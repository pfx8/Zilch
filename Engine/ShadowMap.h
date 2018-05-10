//*****************************************************************************
//
// �V���h�E�}�b�v����[ShadowMap.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADOW_MAP_H_
#define _SHADOW_MAP_H_

#include "Engine.h"
#include "input.h"
#include "Shader.h"

#include "Model/Model.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class ShadowMap
{
private:
	
	LPDIRECT3DTEXTURE9		mShadowMap;			// �V���h�E�}�b�v�̃e�N�X�`��
	LPDIRECT3DSURFACE9      mShadowMapDepth;	// �V���h�E�}�b�v�̐[�x�o�b�t�@�T�[�t�F�C�X
	

	// ���C�g�𒆐S�ɂ��ĕϊ��s������
	D3DXMATRIX				mTargetWVP;
	D3DXMATRIX				mLightView;
	D3DXMATRIX				mLightProjection;

	D3DXMATRIX				mShadowWVP;			// mTargetWVP * mLightView * mLightProjection

public:
	Shader*					mShader;
	unsigned int			mMapSize = 512;
	GameObject*				mShadowTarget;

	D3DXVECTOR3				mLightPos;
	D3DXVECTOR3				mLightAt;
	D3DXVECTOR3				mLightUp;

	ShadowMap(Shader* shader, D3DXVECTOR3 lightPos);
	~ShadowMap();

	void update();								// �V���h�E�}�b�v�X�V
	void draw(Model* model);					// �V���h�E�}�b�v��`��
};

#endif // !_SHADOW_MAP_H_
