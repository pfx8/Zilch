//*****************************************************************************
//
// �}�e���A������ [Material.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Mesh.h"
#include "Model.h"
#include "Texture.h"

#include "..\Engine.h"
#include "..\Resources.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Material
{
private:

public:
	wstring				mName;					// �}�e���A���̖��O
	Model*				mParentModel;			// �������f���|�C���^
	D3DXVECTOR3			mAmbient;				// ����
	D3DXVECTOR3			mDiffuse;				// �g�U���ˌ�
	D3DXVECTOR3			mSpecular;				// ���ʔ��ˌ�
	float				mShininess;				// ����
	vector<Texture*>	mTextures;				// �e�N�X�`��

	// �}�e���A�����Ȃ���΃f�t�H���g�ŏ�����
	Material(aiMaterial* mat, Model* model);
	~Material(void);

	// �}�e���A����ǂݍ���
	void loadingMaterial(aiMaterial* mat);

	// �}�e���A���ɂ���ăe�N�X�`����ǂݍ���
	void addTextureFromResources(aiMaterial* mat, aiTextureType mType);

	// Assimp����ǂݍ��܂ꂽ�e�N�X�`���p�X���΃p�X�ɕϊ�
	wstring searchTexturePath(wstring texturePathFromAssimp);
};

#endif // !_MATERIAL_H
