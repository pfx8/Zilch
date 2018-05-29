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
Model::Model(wstring const& path)
{
	// Assimp�Ń��f����ǂݍ���
	loadModel(path);

	// Debug�E�C���h��
	wcout << "<Scene> loading <Model> " << path << " ... successed!" << endl;
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
HRESULT Model::loadModel(wstring const& wPath)
{
	// �p�X��ۑ�
	this->mPath = wPath;
	// Assimp�œǂݍ��ނ��߂�wstring -> string
	string path = wStringToString(wPath);

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

	// ���f�������擾
	this->mModelInfo.numMeshes = scene->mNumMeshes;
	this->mModelInfo.numMaterials = scene->mNumMaterials;
	this->mModelInfo.numAnimations = scene->mNumAnimations;
	this->mModelInfo.numTextures = scene->mNumTextures;

	// Ex
	this->mModelInfo.numLights = scene->mNumLights;
	this->mModelInfo.numCameras = scene->mNumCameras;

	// �A�j���[�V�������`�F�b�N
	checkAnimation(scene);

	// ���[�g�m�[�h���珈�����n�߂�
	processNode(scene->mRootNode, scene);

	return S_OK;
}

//*****************************************************************************
//
// �m�[�h����
//
//*****************************************************************************
void Model::processNode(aiNode* node, const aiScene* scene)
{
	// ���b�V���m�[�h����
	for (unsigned int count = 0; count < node->mNumMeshes; count++)
	{
		// scene��mMeshes�͖{���̃��b�V���f�[�^�A�����node��mMesher�̓��b�V���̃C���f�b�N�X
		aiMesh* aiMesh = scene->mMeshes[node->mMeshes[count]];
		this->mMeshes.push_back(new Mesh(aiMesh, this->mBones, scene, this->mPath, this));

		//cout << node->mTransformation.a1 << ", " << node->mTransformation.a2 << ", " << node->mTransformation.a3 << ", " << node->mTransformation.a4 << endl;
		//cout << node->mTransformation.b1 << ", " << node->mTransformation.b2 << ", " << node->mTransformation.b3 << ", " << node->mTransformation.b4 << endl;
		//cout << node->mTransformation.c1 << ", " << node->mTransformation.c2 << ", " << node->mTransformation.c3 << ", " << node->mTransformation.c4 << endl;
		//cout << node->mTransformation.d1 << ", " << node->mTransformation.d2 << ", " << node->mTransformation.d3 << ", " << node->mTransformation.d4 << endl;
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
	for (unsigned int count = 0; count < scene->mNumAnimations; count++)
	{
		// �A�j���[�V��������͂��ĕۑ�
		aiAnimation* animation = scene->mAnimations[count];
		this->mAnimationes.push_back(new Animation(animation));
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
// ���f����`��
//
//*****************************************************************************
void Model::drawModel(Shader* shader, bool isOutline)
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
		it->drawModel(shader, isOutline);
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