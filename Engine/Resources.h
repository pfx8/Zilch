//*****************************************************************************
//
// ���\�[�X�Ǘ� [Resources.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "Engine.h"
#include "Model\Mesh.h"
#include "Model\Model.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Resources
{
private:
	map<string, Model*>				mModels;		// ���f��
	map<string, Texture*>			mTextures;		// �e�N�X�`��
	LPDIRECT3DDEVICE9				mD3DDevice;		// D3D�f�o�C�X

public:
	Resources();
	~Resources();
	
	void loadModel(string name, string path);		// Assimp�Ń��f����ǂݍ���
	Model *GetModel(string name);					// ���f���𖼑O�ɂ���Ď擾
	void LoadTexture(string name, string path);		// Assimp�Ńe�N�X�`����ǂݍ���
	Texture *GetTexture(string name);				// �e�N�X�`���𖼑O�ɂ���Ď擾
};

#endif // !_RESOURCES_H_

