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
Model::Model(string name, string const &path)
{
	// ���f���̖��O��������
	this->mName = name;

	// Assimp�Ń��f����ǂݍ���
	loadModel(path);
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
	// Assimp�̃C���|�[�g�����
	Assimp::Importer import;
	// Assimp�V�[�������
	const aiScene* scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality | aiProcess_FixInfacingNormals | aiProcess_ConvertToLeftHanded);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		// Debug�E�C���h��
		cout << "<Error> Assimp::" << import.GetErrorString() << endl;
		return E_FAIL;
	}

	// �A�j���[�V�������`�F�b�N
	checkAnimation(scene);

	// ���[�g�m�[�h���珈�����n�߂�
	processNode(scene->mRootNode, scene);

	// Debug�E�C���h��
	cout << "<Scene> loading " << path << " ... successed!" << endl;

	return S_OK;
}

//*****************************************************************************
//
// �m�[�h����
//
//*****************************************************************************
void Model::processNode(aiNode* node, const aiScene* scene)
{
	// �������̃m�[�h�Ƀ��b�V��������Ώ�������
	for (unsigned int count = 0; count < node->mNumMeshes; count++)
	{
		// scene��mMeshes�͖{���̃��b�V���f�[�^�A�����node��mMesher�̓��b�V���̃C���f�b�N�X
		aiMesh* aiMesh = scene->mMeshes[node->mMeshes[count]];
		this->mMeshes.push_back(new Mesh(aiMesh, this->mBones, scene));

		// ���`�F�b�N
		createBone(aiMesh);
	}

	// �q���m�[�h�𓯂��悤�ɏ�������
	for (unsigned int count = 0; count < node->mNumChildren; count++)
	{
		processNode(node->mChildren[count], scene);
	}
}

//*****************************************************************************
//
// �����邩�ǂ������`�F�b�N
//
//*****************************************************************************
void Model::checkBone(aiMesh* mesh)
{

}

//*****************************************************************************
//
// ���f���̓A�j���[�V�������܂߂Ă邩�ǂ������`�F�b�N
//
//*****************************************************************************
void Model::checkAnimation(const aiScene* scene)
{
	if (scene->mNumAnimations != 0)
	{
		// �A�j���[�V��������͂��ĕۑ�

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
	//this->mAnimationes[this->mCurAnimation]->updateBoneTransforms(timeInSeconds, this->mBones, this->mTransforms);
}

//*****************************************************************************
//
// ���f�[�^����͂��ĕۑ�
//
//*****************************************************************************
void Model::createBone(aiMesh* mesh)
{
	for (unsigned int count = 0; count < mesh->mNumBones; count++)
	{
		
	}
}

//*****************************************************************************
//
// �m�[�h���g���o�[�X
//
//*****************************************************************************
void Model::traverseNode(Node* node, unsigned int level)
{
	string space;

	for (unsigned count = 0; count < level; count++)
	{
		space += "  ";
	}

	ImGui::Text("%s%s", space.c_str(), node->mName.c_str());

	for (auto it : node->mChildren)
	{
		traverseNode(it, level + 1);
	}
}

//*****************************************************************************
//
// ���f����`��
//
//*****************************************************************************
void Model::drawModel(Shader* shader)
{
	D3DXMATRIX mat[87] = { };

	unsigned int count = 0;
	for (auto it : this->mBones)
	{
		mat[count] = it->mFinaTransform;
		//cout << "<Test><Mat> : " << it->mFinaTransform._11 << ", " << it->mFinaTransform._12 << ", " << it->mFinaTransform._13 << endl;
		count++;
	}

	// ���̍s����V�F�[�_�[�ɓn��
	HRESULT hr;
	hr = shader->mEffect->SetMatrixArray("boneMatrices", mat, 87);

	// �e���b�V����`��
	for (auto it : mMeshes)
	{
		it->drawModel(shader);
	}
}

//*****************************************************************************
//
// ���f���̃V���h�E�}�b�v��`��
//
//*****************************************************************************
void Model::drawShadow(Shader* shader)
{
	// �e���b�V���̃V���h�E�}�b�v��`��
	for (auto it : mMeshes)
	{
		it->drawShadow(shader);
	}
}