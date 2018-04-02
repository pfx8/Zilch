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
#include "..\Engine\Shader.h"

struct Vertex 
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;

	// �v���X�C���t�H���[�V����
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 bitangent;
};

struct Texture
{
	LPDIRECT3DTEXTURE9 point;
	string type;
	string path;
};

class Mesh
{
private:
	LPDIRECT3DVERTEXBUFFER9			mVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9			mIndexBuffer;	// ���_�C���f�b�N�X�o�b�t�@
	IDirect3DVertexDeclaration9*	mVertexDecl;	// ���_�V�F�[�_�[�錾
	LPDIRECT3DDEVICE9				mD3DDevice;	// D3D�f�o�C�X

	//-----------Assimp-----------//
	void SetupMesh();

public:
	int							m_polygonNum;	// �|���S����
	int							m_vertexNum;	// ���_��
	DX_VERTEX_3D*				m_vertex;		// ���_�z��
	int							m_IndexNum;		// ���_�C���f�b�N�X��
	int*						m_Index;		// ���_�C���f�b�N�z��,[0,1,2][0,2,3]...
	
	Mesh();
	~Mesh();

	void DrawDXMesh();			// ���b�V����`��
	HRESULT MakeBuffer();		// �`��p�e�o�b�t�@�����


	//-----------Assimp-----------//
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures);

	// ���b�V���f�[�^
	vector<Vertex>				mVertices;
	vector<unsigned int>		mIndices;
	vector<Texture>				mTextures;

	void Draw(Shader *shader);	// �h���[
};



#endif // !_MESH_H_
