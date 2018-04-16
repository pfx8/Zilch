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
#include "Animation.h"
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
	enum MeshType					mMeshType;									// ���b�V���^�C�v
	HRESULT loadModel(string const &path);									// ���f����ǂݍ���
	void processNode(aiNode *node, const aiScene *scene);			// �m�[�h����

public:
	vector<Mesh*>					mMeshes;					// ���b�V���f�[�^
	vector<Animation*>			mAnimationes;			// �A�j���[�V�����f�[�^

	Model(MeshType type, string const &path);
	~Model();

	void addAnimation(Animation* animation);		// �A�j���[�V�����f�[�^��ǂݍ���
	void draw(Transform* trans, Camera* camera);	// ���f����`�悷��
};

#endif // !_MODEL_H_

