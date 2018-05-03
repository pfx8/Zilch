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
	enum MeshType						mMeshType;				// ���b�V���^�C�v
	unsigned int						mCurAnimation = 0;		// ���݂̃A�j���[�V�����ԍ�

	HRESULT loadModel(string const &path);						// ���f����ǂݍ���
	void processNode(aiNode *node, const aiScene *scene);		// �m�[�h����

public:
	string							mName;						// ���f�����O
	vector<Mesh*>					mMeshes;					// ���b�V���f�[�^
	vector<Animation*>				mAnimationes;				// �A�j���[�V�����f�[�^
	vector<Bone*>					mBones;						// ���f�[�^
	vector<D3DXMATRIX>				mTransforms;				// �e���̕ϊ��s��

	Model(MeshType type, string name, string const &path);
	~Model();

	void addAnimation(Animation* animation);						// �A�j���[�V�����f�[�^��ǂݍ���
	void updateAnimation(float timeInSeconds);						// �A�j���[�V�����X�V
	void draw(Shader* shader);										// ���f���̃V���h�E�}�b�v��`��
	void draw(Shader* shader, Transform* trans, Camera* camera);	// ���f����`��
	void traverseNode(Node* node, unsigned int level);				// �m�[�h���g���o�[�X
	void drawImGui();												// ���f���̏���ImGui�ŏo��
};

#endif // !_MODEL_H_

