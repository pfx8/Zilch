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
#include "..\Engine\Engine.h"
#include "..\Engine\Material.h"
#include "..\Engine\Shader.h"

//--------------Assimp--------------//
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Model
{
private:
	D3DXMATRIX		wMatrix;	// ���[���h�ϊ��}�g���b�N�X

	void SetWorldMatrix();						// ���[���h�ϊ�
	void RotationVecUp(float angle);			// ������̃x�N�g���ɂ��ĉ�]

	HRESULT Load(const char *path);				// ���f�������[�h����
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

public:
	D3DXVECTOR3		pos;			// �ʒu
	D3DXVECTOR3		rot;			// ��]
	D3DXVECTOR3		scl;			// �g��k��
	D3DXVECTOR3		upVector;		// �J�����̏�����x�N�g��
	D3DXVECTOR3		lookVector;		// �J�����̒��������x�N�g��
	D3DXVECTOR3		rightVector;	// �J�����̉E�����x�N�g��

	LPD3DXMESH						meshPoint;			// ���b�V�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9				meshTexturePoint;	// �e�N�X�`���}�l�W�����g
	Material*						material;			// �}�e���A�����ւ̃|�C���^
	IDirect3DVertexDeclaration9*	vertexDecl;			// ���_�錾

	vector<Mesh> mMeshes;			// ���b�V���f�[�^

	Model();
	Model(const char *path)
	{
		Load(path);
	};
	~Model();

	void Update();	// �X�V
	void Draw(Shader* shader2D, D3DXMATRIX* vMatrix, D3DXMATRIX* pMatrix);	// ���f����`�悷��
};

#endif // !_MODEL_H_

