//*****************************************************************************
//
// ���f������ [Model.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

#include "Animation.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

#include "..\Engine.h"
#include "..\Shader.h"

#include "..\..\Component\Camera.h"
#include "..\..\Component\Transform.h"

//*****************************************************************************
//
// �\���̒�`
//
//*****************************************************************************
struct ModelInfo
{
	unsigned int numMeshes;
	unsigned int numMaterials;
	unsigned int numAnimations;
	unsigned int numTextures;
	unsigned int numLights;
	unsigned int numCameras;
};


//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Model
{
	friend class MeshRender;
private:
	ModelInfo						mModelInfo;						// ���f�����\����

	HRESULT loadModel(wstring const& wPath);						// ���f����ǂݍ���
	void processNode(aiNode *node, const aiScene *scene);			// �m�[�h����

public:
	unsigned int					mCurAnimation = 0;				// ���݂̃A�j���[�V�����ԍ�
	wstring							mPath;							// ���f���p�X
	vector<Animation*>				mAnimationes;					// �A�j���[�V�����f�[�^
	vector<Bone*>					mBones;							// ���f�[�^
	vector<D3DXMATRIX>				mTransforms;					// �e���̕ϊ��s��
	vector<Mesh*>					mMeshes;						// ���b�V���f�[�^
	vector<Material*>				mMaterials;						// �}�e���A���f�[�^
	vector<Texture*>				mTextures;						// �e�N�N�V���f�[�^

	Model(wstring const& wPath);
	~Model(void);

	void checkAnimation(const aiScene* scene);						// ���f���̓A�j���[�V�������܂߂Ă邩�ǂ������`�F�b�N
	void addAnimation(Animation* animation);						// �A�j���[�V�����f�[�^��ǂݍ���
	void updateAnimation(float timeInSeconds);						// �A�j���[�V�����X�V

	void drawShadow(Shader* shader);								// ���f���̃V���h�E�}�b�v��`��
	void drawModel(Shader* shader, bool isOutline);					// ���f����`��

	void checkBone(aiMesh* mesh);									// �����邩�ǂ������`�F�b�N
};

#endif // !_MODEL_H_

