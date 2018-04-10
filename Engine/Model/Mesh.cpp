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
Mesh::Mesh(aiMesh* mesh, const aiScene* scene)
{
	// �o�b�t�@�|�C���^��������
	mVertexBuffer = nullptr;
	mIndexBuffer = nullptr;

	// ���_�t�H�[�}�b�g�錾�|�C���g��������
	mVertexDecl = nullptr;

	// ���b�V����ǂݍ���
	loadingMesh(mesh, scene);
	// ���b�V���̃o�b�t�@�����
	SetupMesh();
}

//*****************************************************************************
//
// ���b�V����ǂݍ���
//
//*****************************************************************************
void Mesh::loadingMesh(aiMesh *mesh, const aiScene *scene)
{
	cout << "   <Mesh Name> : [" << mesh->mName.C_Str() << "]" << endl;

	// ���_����
	for (unsigned int count = 0; count < mesh->mNumVertices; count++)
	{
		Vertex vertex;

		// �ʒu
		vertex.pos.x = mesh->mVertices[count].x;
		vertex.pos.y = mesh->mVertices[count].y;
		vertex.pos.z = mesh->mVertices[count].z;

		// �@��
		vertex.nor.x = mesh->mNormals[count].x;
		vertex.nor.y = mesh->mNormals[count].y;
		vertex.nor.z = mesh->mNormals[count].z;

		// UV���W
		if (mesh->mTextureCoords[0])	// �e�N�X�`��0����(Max��8��)
		{
			vertex.tex.x = mesh->mTextureCoords[0][count].x;
			vertex.tex.y = mesh->mTextureCoords[0][count].y;
		}
		else
		{
			vertex.tex = D3DXVECTOR2(0.0f, 0.0f);
		}

		// �ڐ�(Tangents)
		/*if (mesh->mTangents)
		{
		vertex.tangent.x = mesh->mTangents[count].x;
		vertex.tangent.y = mesh->mTangents[count].y;
		vertex.tangent.z = mesh->mTangents[count].z;
		}
		else
		{
		vertex.tangent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}*/

		// �]�ڐ�(Bitangents)
		/*if (mesh->mBitangents)
		{
		vertex.bitangent.x = mesh->mBitangents[count].x;
		vertex.bitangent.y = mesh->mBitangents[count].y;
		vertex.bitangent.z = mesh->mBitangents[count].z;
		}
		else
		{
		vertex.bitangent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}*/

		// �擾�������_�𒸓_�R���e�i�̖����ɒǉ�
		this->mVertices.push_back(vertex);
	}

	// �C���f�b�N�X����
	for (unsigned int count = 0; count < mesh->mNumFaces; count++)
	{
		aiFace face = mesh->mFaces[count];

		for (unsigned int i = 0; i < face.mNumIndices; i++)
		{
			// �t�F�[�X�ɂ���Ċe���_�̃C���f�b�N�X���擾
			this->mIndices.push_back(face.mIndices[i]);
		}
	}

	// �}�e���A������
	{
		// �t�F�[�X�̃}�e���A�����擾
		aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
		Material* mat = new Material(aiMat);
		// ���b�V���̃}�e���A���ɓ����
		this->mMaterials.push_back(mat);
	}

	//cout << "      <Vertices Nums> : [" << this->mVertices.size() << "]" << endl
	//	<< "      <Indices Nums> : [" << this->mIndices.size() << "]" << endl
	//	<< "      <Materials Nums> : [" << this->mMaterials.size() << "]" << endl;
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
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// ���_�V�F�[�_�[�錾
	{
		D3DVERTEXELEMENT9 Decl[] =		// ���_�f�[�^�̃��C�A�E�g���`
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		pD3DDevice->CreateVertexDeclaration(Decl, &mVertexDecl);
	}

	// ���_�o�b�t�@�쐬
	if (FAILED(pD3DDevice->CreateVertexBuffer(mVertices.size() * sizeof(Vertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &mVertexBuffer, NULL)))
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
		//vertices[count].tangent = it.tangent;
		//vertices[count].bitangent = it.bitangent;

		count++;
	}

	// ���_�f�[�^���A�����b�N
	mVertexBuffer->Unlock();

	// ���_�C���f�b�N�X�o�b�t�@�쐬
	if (FAILED(pD3DDevice->CreateIndexBuffer(mIndices.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mIndexBuffer, NULL)))
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
void Mesh::draw(Transform* trans, Camera* camera)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();
	Resources* resource = getResources();
	Shader* shader = resource->getShader("phongShading");

	// �e�N�j�b�N��ݒ�
	shader->mEffect->SetTechnique("defaultRender");

	// ���f���̃��[���h�ϊ��s����V�F�[�_�[�ɓn��
	shader->mEffect->SetMatrix("worldMatrix", &trans->mWorldMatrix);

	// �J�����̍s����V�F�[�_�[�ɓn��
	shader->mEffect->SetMatrix("viewMatrix", &camera->mViewMatrix);
	shader->mEffect->SetMatrix("projectionMatrix", &camera->mProjectionMatrix);

	// �e�N�X�`����n��
	LPDIRECT3DTEXTURE9	 diffuse = this->mMaterials.at(0)->mTextures.at(0)->mTex;
	shader->mEffect->SetTexture("diffuse", diffuse);

	// �`��
	UINT passNum = 0;
	shader->mEffect->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		// �e�p�X��`��
		shader->mEffect->BeginPass(count);

		HRESULT hr;
		hr = pD3DDevice->SetVertexDeclaration(mVertexDecl);							// ���_�錾��ݒ�
		hr = pD3DDevice->SetStreamSource(0, mVertexBuffer, 0, sizeof(Vertex));				// ���_�o�b�t�@��ݒ�
		hr = pD3DDevice->SetIndices(mIndexBuffer);											// �C���f�b�N�X�o�b�t�@��ݒ�
		unsigned int vertexNums = mVertices.size();
		unsigned int faceNums = mIndices.size() / 3;
		hr = pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, vertexNums, 0, faceNums);	// �|���S���̕`��

		shader->mEffect->EndPass();
	}
	shader->mEffect->End();
}