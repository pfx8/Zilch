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

//--------------Assimp--------------//
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Material
{
	friend class Model;
private:
	vector<Texture*>		mTexturesLoaded;				// �e�N�X�`��
	string							mName;								// �}�e���A���̖��O

public:
	D3DXVECTOR3			mAmbient;				// ����
	D3DXVECTOR3			mDiffuse;				// �g�U���ˌ�
	D3DXVECTOR3			mSpecular;				// ���ʔ��ˌ�

	float							mShininess;			// ����

	// �}�e���A�����Ȃ���΃f�t�H���g�ŏ�����
	Material(aiMaterial* mat);
	~Material();

	// �}�e���A����ǂݍ���
	void loadingMaterial(aiMaterial* mat);

	// �}�e���A���ɂ���ăe�N�X�`����ǂݍ���
	vector<Texture*> loadMaterialTexture(aiMaterial* mat, aiTextureType mType, string typeName);
};

#endif // !_MATERIAL_H
