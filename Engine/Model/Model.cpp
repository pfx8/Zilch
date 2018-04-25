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
	string fileName = path.substr(path.find_last_of("/") + 1, path.find_first_of("."));	// exp c:/aaa/bbb/ccc.fbx -> ccc

	switch (this->mMeshType)
	{
	case MT_default:
		cout << endl << "<Model><default> : [" << fileName << "]" << endl;
		break;
	case MT_withBone:
		cout << endl << "<Model><withBone> : [" << fileName << "]" << endl;
		break;
	}

	loadModel(path);

	// ���f���\����debug�E�C���h�ɏo��
	//unsigned msehNum = 0;
	//unsigned int meshesNum = 1;
	//for (auto it : this->mMeshes)
	//{
	//	cout << "  |- <Mesh><No." << meshesNum << "> : [" << it->mName << "]" << endl;
	//	meshesNum++;

	//	// material
	//	unsigned int materialsNum = 1;
	//	for (auto it1 : it->mMaterials)
	//	{
	//		cout << "    |- <Material><No." << materialsNum << "> : [" << it1->mName << "]" << endl;
	//		materialsNum++;

	//		// texture
	//		unsigned int texturesNum = 1;
	//		for (auto it2 : it1->mTextures)
	//		{
	//			cout << "      |- <Texture><No." << texturesNum << "> : [" << it2->mName << "]" << endl;
	//			texturesNum++;
	//		}
	//	}
	//}

	// ImGui�Ń��b�V���̍\�z��\��
	//ImGui::Begin("Model");
	//�X�N���[��
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
		this->mMeshes.push_back(new Mesh(this->mMeshType, aiMesh, this->mBones, scene));
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
	this->mAnimationes[this->mCurAnimation]->updateBoneTransforms(timeInSeconds, this->mBones, this->mTransforms);
}

//*****************************************************************************
//
// ���f���̃V���h�E�}�b�v��`��
//
//*****************************************************************************
void Model::draw(Shader* shader)
{
	// �e���b�V���̃V���h�E�}�b�v��`��
	for (auto it : mMeshes)
	{
		it->draw(shader);
	}
}

//*****************************************************************************
//
// ���f����`��
//
//*****************************************************************************
void Model::draw(Shader* shader, Transform* trans, Camera* camera)
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
		it->draw(shader, trans, camera);
	}
}