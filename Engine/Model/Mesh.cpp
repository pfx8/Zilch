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
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture*>  textures)
{
	LPDIRECT3DDEVICE9	D3dDevice = GetDevice();

	// ���b�V���f�[�^�R���e�i��������
	mVertices = vertices;
	mIndices = indices;
	mTextures = textures;

	// �o�b�t�@�|�C���^��������
	mVertexBuffer = nullptr;
	mIndexBuffer = nullptr;

	// ���_�t�H�[�}�b�g�錾�|�C���g��������
	mVertexDecl = nullptr;

	// ���b�V���̃o�b�t�@�����
	SetupMesh();
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Mesh::~Mesh()
{
	RELEASE_POINT(mVertexBuffer);
	RELEASE_POINT(mIndexBuffer);
}

//*****************************************************************************
//
// ���b�V����ݒ�
//
//*****************************************************************************
HRESULT Mesh::SetupMesh()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�V�F�[�_�[�錾
	{
		D3DVERTEXELEMENT9 Decl[] =		// ���_�f�[�^�̃��C�A�E�g���`
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
			{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(Decl, &mVertexDecl);
	}

	// ���_�o�b�t�@�쐬
	if (FAILED(pDevice->CreateVertexBuffer(mVertices.size() * sizeof(Vertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &mVertexBuffer, NULL)))
	{
		cout << "[Error] <Mesh> Make vertex buffer ... fail!" << endl;	// �G���[���b�Z�[�W
		return E_FAIL;
	}
		
	Vertex* vertices = nullptr;
		
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾
	mVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	unsigned int count = 0;
	for (auto it : mVertices)
	{
		vertices[count].pos = it.pos;
		vertices[count].nor = it.nor;
		vertices[count].tex = it.tex;
		vertices[count].tangent = it.tangent;
		vertices[count].bitangent = it.bitangent;

		// test
		//cout << "-> (" << vertices[count].pos.x << ", " << vertices[count].pos.y << ", " << vertices[count].pos.z << ")" << endl;

		count++;
	}

	// ���_�f�[�^���A�����b�N
	mVertexBuffer->Unlock();

	// ���_�C���f�b�N�X�o�b�t�@�쐬
	if (FAILED(pDevice->CreateIndexBuffer(mIndices.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mIndexBuffer, NULL)))
	{
		cout << "[Error] <Mesh> Make index buffer ... fail!" << endl;	// �G���[���b�Z�[�W
		return E_FAIL;
	}

	unsigned int* vertexIndex = nullptr;

	// �C���f�b�N�X �f�[�^�̂�����͈͂����b�N���A���̃C���f�b�N�X�o�b�t�@�������[�ւ̃|�C���^�[���擾
	mIndexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);

	count = 0;
	for (auto it : mIndices)
	{
		vertexIndex[count] = it;
	}

	// �C���f�b�N�X �f�[�^�̃��b�N������
	mIndexBuffer->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// ���b�V�����h���[
//
//*****************************************************************************
void Mesh::draw(Shader *shader)
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