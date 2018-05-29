//*****************************************************************************
//
// ���b�V������ [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "Material.h"
#include "Model.h"
#include "Bone.h"

#include "..\Engine.h"
#include "..\Shader.h"

#include "..\..\Component\Camera.h"
#include "..\..\Component\Transform.h"

//*****************************************************************************
//
// �\���̒�`
//
//*****************************************************************************
// ���_�݌v
struct VertexDesign 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;
	D3DXVECTOR3 tangent;

	// ��
	unsigned int	boneID[NUM_BONES_PER_VEREX] { 0, 0, 0, };					// ����ID
	float			weights[NUM_BONES_PER_VEREX] { 0.0f, 0.0f, 0.0f, 0.0f};		// ���̏d��
};

struct MeshInfo
{
	unsigned int numVertices;
	unsigned int numFaces;
};

//*****************************************************************************
//
//  �񋓑̒�`
//
//*****************************************************************************
typedef enum MeshType
{
	MT_default,
	MT_withBone,
};

//*****************************************************************************
//
// �N���X��`
//
//*****************************************************************************
class Mesh
{
	friend class MeshRender;
private:
	MeshInfo						mMeshInfo;				// ���b�V�����
	Model*							mParentModel;			// �������f���|�C���^
	D3DXVECTOR3						mBoundingBoxMax;		// �o�E���f�B���O�{�b�N�X�}�b�N�X���W�̍ő�l
	D3DXVECTOR3						mBoundingBoxMin;		// �o�E���f�B���O�{�b�N�X�}�b�N�X���W�̍ŏ��l
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;			// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;			// ���_�C���f�b�N�X�o�b�t�@
	IDirect3DVertexDeclaration9*	mVertexDecl;			// ���_�錾

	void createMesh(aiMesh* mesh, vector<Bone*>& bones, const aiScene* scene);							// ���b�V����ǂݍ���
	HRESULT setupMesh();																				// ���b�V�����Z�b�g�A�b�v
	HRESULT setupVertices();																			// ���_���Z�b�g�A�b�v
	HRESULT setupIndexes();																				// �C���f�b�N�X���Z�b�g�A�b�v

	void createBoundingBox(D3DXVECTOR3 vertexPos, D3DXVECTOR3 &boxMax, D3DXVECTOR3 &boxMin);			// �o�E���f�B���O�{�b�N�X�T�C�Y�����

public:
	wstring							mName;					// ���b�V���̖��O
	vector<VertexDesign>			mVertices;				// ���_�f�[�^
	vector<unsigned int>			mIndices;				// ���_�C���f�b�N�X�f�[�^
	vector<Material*>				mMaterials;				// �}�e���A���f�[�^

	Mesh(aiMesh* mesh, vector<Bone*>& bones, const aiScene* scene, wstring modelPath, Model* model);	// ���b�V���̏�����
	~Mesh();

	void drawShadow(Shader* shader);						// ���b�V���̃V���h�E�}�b�v��`��
	void drawModel(Shader* shader, bool isOutline);			// ���b�V����`��
};

#endif // !_MESH_H_
