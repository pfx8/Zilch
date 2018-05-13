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

public:
	unordered_map<wstring, Model*>		mModels;		// ���f��
	unordered_map<wstring, Texture*>	mTextures;		// �e�N�X�`��
	unordered_map<wstring, Shader*>		mShaders;		// �V�F�[�_�[

	Resources();
	~Resources();
	
	void createModel(const wstring path);				// ���f���f�[�^�����
	Model* getModel(wstring name);						// ���f���̖��O�ɂ���Ď擾
	void createTexture(const wstring path);				// �e�N�X�`���f�[�^�����
	Texture* getTexture(wstring name);					// �e�N�X�`���̖��O�ɂ���Ď擾
	void createShader(const wstring path);				// �V�F�[�_�[�f�[�^�����
	Shader* getShader(wstring techniqueName);			// �V�F�[�_�[�̖��O�ɂ���Ď擾
};

#endif // !_RESOURCES_H_

