//*****************************************************************************
//
// ���b�V������ [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include <unordered_map>

#include "Material.h"
#include "Bone.h"
#include "../Engine.h"
#include "../Shader.h"
#include "../../Component/Camera.h"
#include "../../Component/Transform.h"

struct VertexBone 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;

	// �v���X�C���t�H���[�V����
	//D3DXVECTOR3 tangent;
	//D3DXVECTOR3 bitangent;

	// ��
	unsigned int	boneID[NUM_BONES_PER_VEREX];		// ����ID
	float				weights[NUM_BONES_PER_VEREX];		// ���̏d��
};

class Mesh
{
private:
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;	// ���_�C���f�b�N�X�o�b�t�@
	IDirect3DVertexDeclaration9*			mVertexDecl;		// ���_�V�F�[�_�[�錾

	void loadingMesh(aiMesh *mesh, const aiScene *scene);					// ���b�V����ǂݍ���
	HRESULT SetupMesh();																			// ���b�V�����Z�b�g�A�b�v

public:
	// ���b�V���f�[�^
	vector<VertexBone>												mVertices;					// ���_�f�[�^
	vector<unsigned int>									mIndices;					// �C���f�b�N�X�f�[�^
	vector<Material*>											mMaterials;				// �}�e���A���f�[�^

	vector<Bone*>												mBones;						// ���f�[�^


	Mesh(aiMesh *mesh, const aiScene *scene);		// ���b�V���̏�����
	~Mesh();

	void draw(Transform* trans, Camera* camera);	// �h���[
};
#endif // !_MESH_H_
