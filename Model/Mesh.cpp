//*****************************************************************************
//
// ���b�V������ [Mesh.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Mesh.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Mesh::Mesh()
{
	m_vertex = NULL;
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;

	m_D3DDevice = GetDevice();
}

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures)
{
	this->mVertices = vertices;
	this->mIndices = indices;
	this->mTextures = textures;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Mesh::~Mesh()
{
	RELEASE_POINT(m_vertexBuffer);
	RELEASE_POINT(m_indexBuffer);
	RELEASE_CLASS_ARRY_POINT(m_vertex);
	RELEASE_POINT(m_D3DDevice);
}

//*****************************************************************************
//
// �`��p�e�o�b�t�@�����
//
//*****************************************************************************
HRESULT Mesh::MakeBuffer()
{
	// ���_�V�F�[�_�[�錾
	{
		D3DVERTEXELEMENT9 Decl[] =		// ���_�f�[�^�̃��C�A�E�g���`
		{
			{ 0,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
			{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		m_D3DDevice->CreateVertexDeclaration(Decl, &m_vertexDecl);
	}

	// ���_�o�b�t�@�쐬
	{
		if (FAILED(m_D3DDevice->CreateVertexBuffer(m_vertexNum * sizeof(DX_VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_DX_VERTEX_3D, D3DPOOL_MANAGED, &m_vertexBuffer, NULL)))
		{
			cout << "[Error] Make <Mesh> vertex buffer ... Fail!" << endl;	// �G���[���b�Z�[�W
			return E_FAIL;
		}

		DX_VERTEX_3D* vertices = NULL;
		m_vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
		for (int count = 0; count < m_vertexNum; count++)
		{
			vertices[count].position.x = m_vertex[count].position.x;
			vertices[count].position.y = m_vertex[count].position.y;
			vertices[count].position.z = m_vertex[count].position.z;
			vertices[count].position.w = m_vertex[count].position.w;

			vertices[count].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
		}
		m_vertexBuffer->Unlock();
	}

	// ���_�C���f�b�N�X�o�b�t�@�쐬
	{
		if (FAILED(m_D3DDevice->CreateIndexBuffer(m_IndexNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
		{
			cout << "[Error] Make <Mesh> vertex index buffer ... Fail!" << endl;	// �G���[���b�Z�[�W
			return E_FAIL;
		}

		int* vertexIndex = NULL;		// �C�f�b�N�X�̒��g�𖄂߂�
		m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// �C���f�b�N�X �f�[�^�̂�����͈͂����b�N���A���̃C���f�b�N�X �o�b�t�@�[ �������[�ւ̃|�C���^�[���擾����
		int i = 0;
		for (int count = 0; count < m_IndexNum; count++)
		{
			vertexIndex[count] = m_Index[count];
			//cout << vertexIndex[count] << ",";
			cout << m_Index[count] << ",";
			i++;
			if (i == 3)
			{
				i = 0;
				cout << endl;
			}
		}
		m_indexBuffer->Unlock();	// �C���f�b�N�X �f�[�^�̃��b�N����������
	}

	return S_OK;
}

//*****************************************************************************
//
// ���b�V����`��
//
//*****************************************************************************
void Mesh::DrawDXMesh()
{
	D3DXMATRIX wMatrix;
	// ���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(&wMatrix);
	// ���[���h�}�g���N�X�̏�����
	m_D3DDevice->SetTransform(D3DTS_WORLD, &wMatrix);

	// ���_�o�b�t�@���X�g���[���ɓ����
	m_D3DDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(DX_VERTEX_3D));
	// ���_�t�H�[�}�b�g��ݒ�
	m_D3DDevice->SetFVF(FVF_DX_VERTEX_3D);
	// ���_�C���f�b�N�X��ݒ�
	m_D3DDevice->SetIndices(m_indexBuffer);
	// �`��
	m_D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexNum, 0, m_IndexNum);
}

//*****************************************************************************
//
// ���b�V����ݒ�
//
//*****************************************************************************
void Mesh::SetupMesh()
{

}

//*****************************************************************************
//
// ���b�V�����h���[
//
//*****************************************************************************
void Mesh::Draw(Shader *shader)
{

}