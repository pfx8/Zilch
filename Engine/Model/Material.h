//*****************************************************************************
//
// �}�e���A������ [Material.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Texture.h"
#include "../Engine.h"
#include "../Resources.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Material
{
private:

public:
	string				mName;					// �}�e���A���̖��O
	vector<Texture*>		mTextures;				// �e�N�X�`��
	D3DXVECTOR3			mAmbient;				// ����
	D3DXVECTOR3			mDiffuse;				// �g�U���ˌ�
	D3DXVECTOR3			mSpecular;				// ���ʔ��ˌ�
	float				mShininess;				// ����

	// �}�e���A�����Ȃ���΃f�t�H���g�ŏ�����
	Material(aiMaterial* mat);
	~Material();

	// �}�e���A����ǂݍ���
	void loadingMaterial(aiMaterial* mat);

	// �}�e���A���ɂ���ăe�N�X�`����ǂݍ���
	void addTextureFromResources(aiMaterial* mat, aiTextureType mType);
};

#endif // !_MATERIAL_H
