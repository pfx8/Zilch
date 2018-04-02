//*****************************************************************************
//
// ���\�[�X�Ǘ��N���X [ResourcesManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "Engine.h"
#include "Model\Mesh.h"
#include "Model\Model.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class ResourcesManager
{
private:
	map<string, Model*> mModels;
	map<string, Texture*> mTextures;

	LPDIRECT3DDEVICE9				mD3DDevice;		// D3D�f�o�C�X

public:
	ResourcesManager();
	~ResourcesManager();
	
	void loadModel(string name, string path);					// Assimp�Ń��f����ǂݍ���
	Model *GetModel(string name);								// ���f���𖼑O�ɂ���Ď擾
	void LoadTexture(string name, string path, TextureType type);					// Assimp�Ńe�N�X�`����ǂݍ���
	Texture *GetTexture(string name);							// �e�N�X�`���𖼑O�ɂ���Ď擾
};

#endif // !_RESOURCES_MANAGER_H_

