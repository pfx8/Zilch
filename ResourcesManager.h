//*****************************************************************************
//
// ���\�[�X�Ǘ��N���X [ResourcesManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include <map>

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class ResourcesManager
{
private:
	// �e�N�X�`��
	std::map < std::string, std::string> m_textureList;	// �e�N�X�`�����X�g
	std::string GetTextureStruct(std::string name);		// �e�N�X�`���p�X���擾

	// Fbx�t�@�C��
	std::map < std::string, std::string> m_fbxList;	// Fbx���X�g
public:
	ResourcesManager();
	~ResourcesManager();

	HRESULT LoadTexture(std::string name, LPDIRECT3DTEXTURE9* texturePoint);	// �e�N�X�`����ǂݍ���
	std::string GetFbxPath(std::string name);		// Fbx�p�X���擾
};

#endif // !_RESOURCES_MANAGER_H_

