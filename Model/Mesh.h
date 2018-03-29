//*****************************************************************************
//
// ���b�V������ [Mesh..h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "..\Engine\Engine.h"

struct Vertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tes;
};

struct Texture
{
	unsigned int id;
	string tyoe;
};

class Mesh
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;	// ���_�C���f�b�N�X�o�b�t�@
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// ���_�V�F�[�_�[�錾
	LPDIRECT3DDEVICE9				m_D3DDevice;		// D3D�f�o�C�X

public:
	int							m_polygonNum;	// �|���S����
	int							m_vertexNum;	// ���_��
	DX_VERTEX_3D*				m_vertex;		// ���_�z��
	int							m_IndexNum;		// ���_�C���f�b�N�X��
	int*						m_Index;		// ���_�C���f�b�N�z��,[0,1,2][0,2,3]...

	// ���b�V���f�[�^
	vector<Vertex>				mVertices;
	vector<unsigned int>		mIndices;
	vector<Texture>				mTextures;
	
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures);
	Mesh();
	~Mesh();

	void DrawDXMesh();		// ���b�V����`��
	HRESULT MakeBuffer();		// �`��p�e�o�b�t�@�����
};



#endif // !_MESH_H_
