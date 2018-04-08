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
#include "../Shader.h"
#include "../../Component/Camera.h"
#include "../../Component/Transform.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Model
{
private:
	HRESULT loadModel(string const &path);									// ���f����ǂݍ���
	void processNode(aiNode *node, const aiScene *scene);			// �m�[�h����

public:
	vector<Mesh*>					mMeshes;					// ���b�V���f�[�^

	Model(string const &mPath);
	~Model();

	void draw(Transform* trans, Camera* camera);	// ���f����`�悷��
};

#endif // !_MODEL_H_

