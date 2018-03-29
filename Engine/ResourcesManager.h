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
#include "..\Model\Mesh.h"
#include "..\Model\Model.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class ResourcesManager
{
private:
	// �e�N�X�`��
	map < string, string> textures;
	string GetTextureStruct(string name);		// �e�N�X�`���p�X���擾

	// ���b�V��
	map < string, string> meshes;
	string GetMeshPath(string name);		// ���b�V���p�X���擾	

	// ���f��
	map<string, Model*> models;

public:
	ResourcesManager();
	~ResourcesManager();

	HRESULT LoadTexture(string name, LPDIRECT3DTEXTURE9* texturePoint);	// �e�N�X�`����ǂݍ���
	HRESULT LoadModel(string name, Model* model);						// ���f����ǂݍ���
	
	void LoadModel(string name, const char *path);						// Assimp�Ń��f����ǂݍ���
	Model *GetModel(string name);										// ���f���𖼑O�ɂ���ăQ�b�g
};

#endif // !_RESOURCES_MANAGER_H_

