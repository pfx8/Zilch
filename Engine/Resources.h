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
#include "Shader.h"
#include "Model/Mesh.h"
#include "Model/Model.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Resources
{
private:

public:
	unordered_map<string, Model*>		mModels;		// ���f��
	unordered_map<string, Texture*>		mTextures;		// �e�N�X�`��
	unordered_map<string, Shader*>		mShaders;		// �V�F�[�_�[

	Resources();
	~Resources();
	
	void loadModel(enum MeshType type, string name, string path);			// Assimp�Ń��f����ǂݍ���
	Model* getModel(string name);							// ���f���̖��O�ɂ���Ď擾
	void loadTexture(string name, string path);		// �e�N�X�`����ǂݍ���
	Texture* getTexture(string name);						// �e�N�X�`���̖��O�ɂ���Ď擾
	void loadShader(string techniqueName, string path);		// �V�F�[�_�[��ǂݍ���
	Shader* getShader(string techniqueName);							// �V�F�[�_�[�̖��O�ɂ���Ď擾
};

#endif // !_RESOURCES_H_

