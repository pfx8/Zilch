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
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>  textures)
{
	// D3D�f�o�C�X�|�C���^���擾
	this->mD3DDevice = GetDevice();

	// ���b�V���f�[�^�R���e�i��������
	this->mVertices = vertices;
	this->mIndices = indices;
	this->mTextures = textures;

	// �o�b�t�@�|�C���^��������
	this->mVertexBuffer = nullptr;
	this->mIndexBuffer = nullptr;
	this->mVertexDecl = nullptr;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Mesh::~Mesh()
{
	RELEASE_POINT(this->mVertexBuffer);
	RELEASE_POINT(this->mIndexBuffer);
	RELEASE_POINT(this->mVertexDecl);
	RELEASE_POINT(this->mD3DDevice);
}

//*****************************************************************************
//
// �`��p�e�o�b�t�@�����
//
//*****************************************************************************
HRESULT Mesh::MakeBuffer()
{
	//// ���_�V�F�[�_�[�錾
	//{
	//	D3DVERTEXELEMENT9 Decl[] =		// ���_�f�[�^�̃��C�A�E�g���`
	//	{
	//		{ 0,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	//		{ 0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
	//		{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
	//		{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	//		D3DDECL_END()
	//	};
	//	mD3DDevice->CreateVertexDeclaration(Decl, &mVertexDecl);
	//}

	//// ���_�o�b�t�@�쐬
	//{
	//	if (FAILED(mD3DDevice->CreateVertexBuffer(m_vertexNum * sizeof(DX_VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_DX_VERTEX_3D, D3DPOOL_MANAGED, &mVertexBuffer, NULL)))
	//	{
	//		cout << "[Error] Make <Mesh> vertex buffer ... Fail!" << endl;	// �G���[���b�Z�[�W
	//		return E_FAIL;
	//	}

	//	DX_VERTEX_3D* vertices = NULL;
	//	mVertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	//	for (int count = 0; count < m_vertexNum; count++)
	//	{
	//		vertices[count].position.x = m_vertex[count].position.x;
	//		vertices[count].position.y = m_vertex[count].position.y;
	//		vertices[count].position.z = m_vertex[count].position.z;
	//		vertices[count].position.w = m_vertex[count].position.w;

	//		vertices[count].diffuse = D3DCOLOR_RGBA(0, 0, 0, 255);
	//	}
	//	mVertexBuffer->Unlock();
	//}

	//// ���_�C���f�b�N�X�o�b�t�@�쐬
	//{
	//	if (FAILED(mD3DDevice->CreateIndexBuffer(m_IndexNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mIndexBuffer, NULL)))
	//	{
	//		cout << "[Error] Make <Mesh> vertex index buffer ... Fail!" << endl;	// �G���[���b�Z�[�W
	//		return E_FAIL;
	//	}

	//	int* vertexIndex = NULL;		// �C�f�b�N�X�̒��g�𖄂߂�
	//	mIndexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// �C���f�b�N�X �f�[�^�̂�����͈͂����b�N���A���̃C���f�b�N�X �o�b�t�@�[ �������[�ւ̃|�C���^�[���擾����
	//	int i = 0;
	//	for (int count = 0; count < m_IndexNum; count++)
	//	{
	//		vertexIndex[count] = m_Index[count];
	//		//cout << vertexIndex[count] << ",";
	//		cout << m_Index[count] << ",";
	//		i++;
	//		if (i == 3)
	//		{
	//			i = 0;
	//			cout << endl;
	//		}
	//	}
	//	mIndexBuffer->Unlock();	// �C���f�b�N�X �f�[�^�̃��b�N����������
	//}

	return S_OK;
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
	//D3DXMATRIX wMatrix;
	//// ���[���h�}�g���b�N�X������������
	//D3DXMatrixIdentity(&wMatrix);
	//// ���[���h�}�g���N�X�̏�����
	//mD3DDevice->SetTransform(D3DTS_WORLD, &wMatrix);

	//// ���_�o�b�t�@���X�g���[���ɓ����
	//mD3DDevice->SetStreamSource(0, mVertexBuffer, 0, sizeof(DX_VERTEX_3D));
	//// ���_�t�H�[�}�b�g��ݒ�
	//mD3DDevice->SetFVF(FVF_DX_VERTEX_3D);
	//// ���_�C���f�b�N�X��ݒ�
	//mD3DDevice->SetIndices(mIndexBuffer);
	//// �`��
	//mD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertexNum, 0, m_IndexNum);


}