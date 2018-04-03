//*****************************************************************************
//
// ���b�V������ [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "Texture.h"
#include "../Engine.h"
#include "../Shader.h"

struct Vertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;

	// �v���X�C���t�H���[�V����
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 bitangent;
};

class Mesh
{
private:
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;	// ���_�C���f�b�N�X�o�b�t�@
	IDirect3DVertexDeclaration9*	mVertexDecl;	// ���_�V�F�[�_�[�錾

	HRESULT SetupMesh();							// ���b�V�����Z�b�g�A�b�v

public:
	// ���b�V���f�[�^
	vector<Vertex>					mVertices;
	vector<unsigned int>			mIndices;
	vector<Texture>					mTextures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures);
	~Mesh();

	void draw(Shader *shader);	// �h���[
};



#endif // !_MESH_H_
