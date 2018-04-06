//*****************************************************************************
//
// ���f������ [Model.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

#include "Mesh.h"
#include "Material.h"
#include "../Engine.h"
#include "../Resources.h"
#include "../Shader.h"

//--------------Assimp--------------//
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Model
{
private:
	HRESULT loadModel(string const &mPath);								// ���f����ǂݍ���
	void processNode(aiNode *node, const aiScene *scene);			// �m�[�h����
	Mesh* processMesh(aiMesh *mesh, const aiScene *scene);		// ���b�V������

	vector<Texture*> loadMaterialTexture(aiMaterial* mat, aiTextureType mType, string typeName);		// �}�e���A������e�N�X�`����ǂݍ���
	Material* loadMaterial(aiMaterial* mat);

public:
	vector<Mesh*>					mMeshes;					// ���b�V���f�[�^
	vector<Texture*>				mTexturesLoaded;		// �ǂݍ��܂ꂽ�e�N�X�`���f�[�^
	vector<Material*>				mMaterialLoaded;		// �}�e���A���f�[�^

	Model(string const &mPath);
	~Model();

	void draw();	// ���f����`�悷��
};

#endif // !_MODEL_H_

