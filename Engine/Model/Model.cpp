//*****************************************************************************
//
// ���f������ [Model.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Model.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Model::Model(MeshType type, string const &path)
{
	// ���b�V���^�C�v���擾
	this->mMeshType = type;
	// ���f���̖��O���擾
	string fileName = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp c:/aaa/bbb/ccc.fbx -> ccc.fbx

	switch (this->mMeshType)
	{
	case MT_default:
		cout << endl << "<Model> : [" << fileName << "] <default>" << endl;
		break;
	case MT_withBone:
		cout << endl << "<Model> : [" << fileName << "] <withBone>" << endl;
		break;
	}

	loadModel(path);

	//cout << "   <Mesh Nums> : [" << mMeshes.size() << "]" << endl;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Model::~Model()
{
	// delete vector
}

//*****************************************************************************
//
// ���f�������[�h����
//
//*****************************************************************************
HRESULT Model::loadModel(string const &path)
{
	Assimp::Importer import;			// Assimp�̃C���|�[�g�����
	const aiScene *scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality | aiProcess_FixInfacingNormals | aiProcess_ConvertToLeftHanded);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "[Error] Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

	// ���[�g�m�[�h���珈�����n�߂�
	processNode(scene->mRootNode, scene);

	return S_OK;
}

//*****************************************************************************
//
// �m�[�h����
//
//*****************************************************************************
void Model::processNode(aiNode *node, const aiScene *scene)
{
	// �������̃m�[�h�Ƀ��b�V��������Ώ�������
	for (unsigned int count = 0; count < node->mNumMeshes; count++)
	{
		// scene��mMeshes�͖{���̃��b�V���f�[�^�A�����node��mMesher�̓��b�V���̃C���f�b�N�X
		aiMesh* aiMesh = scene->mMeshes[node->mMeshes[count]];
		this->mMeshes.push_back(new Mesh(this->mMeshType, aiMesh, &this->mTransforms, scene));
	}

	// �m�[�h���b�Z�[�W��ۑ�

	// �q���m�[�h�𓯂��悤�ɏ�������
	for (unsigned int count = 0; count < node->mNumChildren; count++)
	{
		processNode(node->mChildren[count], scene);
	}
}

//*****************************************************************************
//
// �A�j���[�V�����f�[�^��ǂݍ���
//
//*****************************************************************************
void Model::addAnimation(Animation* animation)
{
	this->mAnimationes.push_back(animation);
}

//*****************************************************************************
//
// �A�j���[�V�����X�V
//
//*****************************************************************************
void Model::updateAnimation(float timeInSeconds)
{
	this->mAnimationes[this->mCurAnimation]->processBoneTransforms(timeInSeconds, this->mTransforms);
}

//*****************************************************************************
//
// ���f����`��
//
//*****************************************************************************
void Model::draw(Transform* trans, Camera* camera)
{
	// �e���b�V����`��
	for (auto it : mMeshes)
	{
		it->draw(trans, camera);
	}
}