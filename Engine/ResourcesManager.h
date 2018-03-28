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
	map < string, string> textureList;	// �e�N�X�`�����X�g
	string GetTextureStruct(string name);		// �e�N�X�`���p�X���擾

	// ���b�V��
	map < string, string> meshList;	// ���b�V�����X�g
	string GetMeshPath(string name);		// ���b�V���p�X���擾	

public:
	ResourcesManager();
	~ResourcesManager();

	HRESULT LoadTexture(string name, LPDIRECT3DTEXTURE9* texturePoint);	// �e�N�X�`����ǂݍ���
	HRESULT LoadMesh(string name, Model* model);	// ���b�V����ǂݍ���
};

#endif // !_RESOURCES_MANAGER_H_

