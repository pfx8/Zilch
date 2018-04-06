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

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Material
{
	friend class Model;
private:
	vector<Texture>		mTextures;				// �e�N�X�`��
	string							mName;					// �}�e���A���̖��O

public:
	D3DXVECTOR3			mAmbient;				// ����
	D3DXVECTOR3			mDiffuse;				// �g�U���ˌ�
	D3DXVECTOR3			mSpecular;				// ���ʔ��ˌ�

	float							mShininess;			// ����

	Material(string name, D3DXVECTOR3 ambient, D3DXVECTOR3 diffuse, D3DXVECTOR3 specular);
	~Material();
};

#endif // !_MATERIAL_H
