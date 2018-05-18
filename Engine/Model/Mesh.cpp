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
Mesh::Mesh(aiMesh* mesh, vector<Bone*>& bones, const aiScene* scene, wstring modelPath)
{
	// �e�N�X�`���T�����߂ɕۑ�����
	this->mModelPath = modelPath;

	this->mName = stringUTF8ToUnicode(mesh->mName.C_Str());
	this->mMeshInfo.numVertices = mesh->mNumVertices;
	this->mMeshInfo.numFaces = mesh->mNumFaces;
	this->mVertexBuffer = nullptr;
	this->mIndexBuffer = nullptr;
	this->mVertexDecl = nullptr;			// ���_�錾

	// ���b�V����ǂݍ���&���b�V���̃o�b�t�@�����
	createMesh(mesh, bones, scene);
	setupMesh();
}

//*****************************************************************************
//
// ���t�����b�V����ǂݍ���
//
//*****************************************************************************
void Mesh::createMesh(aiMesh* mesh, vector<Bone*>& bones, const aiScene *scene)
{
	unsigned int numBones = bones.size();

	// ���_����
	for (unsigned int count = 0; count < mesh->mNumVertices; count++)
	{
		VertexDesign vertex;

		// Todo 
		// ���𔻒f�ł���@�\

		// blender���W��DX���W���Ⴄ�̂ŁAY����Z�����������Ȃ���
		// �ʒu
		vertex.pos.x = mesh->mVertices[count].x;
		vertex.pos.y = -mesh->mVertices[count].z;
		vertex.pos.z = -mesh->mVertices[count].y; 

		// �@��
		vertex.nor.x = mesh->mNormals[count].x;
		vertex.nor.y = -mesh->mNormals[count].z;
		vertex.nor.z = -mesh->mNormals[count].y;

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

		// �o�E���f�B���O�{�b�N�X�����
		createBoundingBox(vertex.pos, this->mBoundingBoxMax, this->mBoundingBoxMin);
	}

	// ������
	for (unsigned int count = 0; count < mesh->mNumBones; count++)
	{
		unsigned int boneIndex =0;

		// ���̖��O���擾
		string boneName = mesh->mBones[count]->mName.C_Str();
		bool skip = false;

		// vector<Bone*>�ɍ���T��
		for (auto it : bones)
		{
			// �����ǂݍ��񂾍��Ȃ��
			if (it->mName == boneName)
			{
				// vector<Bone>���獜�̔ԍ����擾
				boneIndex = it->mIndex;
				skip = true;
				break;
			}
		}

		// �V�������Ȃ�΁Avector<Bone*>�ɑ���
		if (skip == false)
		{
			// ���ɔԍ���t��
			boneIndex = numBones;
			numBones++;
			// ���f�[�^��ۑ�
			D3DXMATRIX offset = mesh->mBones[count]->mOffsetMatrix[0];		// aiMatrix����D3DXMATRIX�֕ύX
			Bone *bone = new Bone(boneIndex, offset, boneName);
			bones.push_back(bone);
		}

		// ���_�ɍ���������
		for (unsigned int i = 0; i < mesh->mBones[count]->mNumWeights; i++)
		{

			// ���̍��ɑ΂��Ċe�e������Ă钸�_��ID�Əd�݂��擾
			unsigned int vertexID = mesh->mBones[count]->mWeights[i].mVertexId;
			float weight = mesh->mBones[count]->mWeights[i].mWeight;

			// ���_�ɏ�������
			for (unsigned int j = 0; j < NUM_BONES_PER_VEREX; j++)
			{
				if (mVertices.at(vertexID).weights[j] == 0.0f)
				{
					mVertices.at(vertexID).boneID[j] = boneIndex;
					mVertices.at(vertexID).weights[j] = weight;

					// test data
					mVertices.at(vertexID).boneNum++;

					break;
				}
			}
		}
	}

	// �C���f�b�N�X����
	for (unsigned int count = 0; count < mesh->mNumFaces; count++)
	{
		aiFace face = mesh->mFaces[count];

		for (unsigned int i = 0; i < face.mNumIndices; i = i + 3)
		{
			// �t�F�[�X�ɂ���Ċe���_�̃C���f�b�N�X���擾
			// DX�̃|���S���`�����[���͔����v���Ȃ̂ŁA�����ŕύX
			this->mIndices.push_back(face.mIndices[i]);
			this->mIndices.push_back(face.mIndices[i+2]);
			this->mIndices.push_back(face.mIndices[i+1]);
		}
	}

	// �}�e���A������
	{
		// �t�F�[�X�̃}�e���A�����擾
		aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
		Material* mat = new Material(aiMat, this->mModelPath);
		// ���b�V���̃}�e���A���ɓ����
		this->mMaterials.push_back(mat);
	}
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
HRESULT Mesh::setupMesh()
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// ���_�V�F�[�_�[�錾
	{
		D3DVERTEXELEMENT9 Decl[] =		// ���_�f�[�^�̃��C�A�E�g���`
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
			{ 0, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
			D3DDECL_END()
		};
		pD3DDevice->CreateVertexDeclaration(Decl, &this->mVertexDecl);
	}

	setupVertices();

	setupIndexes();

	return S_OK;
}

//*****************************************************************************
//
// ���_���Z�b�g�A�b�v
//
//*****************************************************************************
HRESULT Mesh::setupVertices()
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// ���_�o�b�t�@�쐬
	if (FAILED(pD3DDevice->CreateVertexBuffer(mVertices.size() * sizeof(VertexDesign), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &this->mVertexBuffer, NULL)))
	{
		// Debug�E�C���h��
		cout << "<Error> make vertex buffer ... failed!" << endl;
		return E_FAIL;
	}

	VertexDesign* vertices = nullptr;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾
	this->mVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	unsigned int count = 0;
	for (auto it : this->mVertices)
	{
		vertices[count].pos = it.pos;

		vertices[count].nor = it.nor;
		vertices[count].tex = it.tex;
		//vertices[count].tangent = it.tangent;
		//vertices[count].bitangent = it.bitangent;

		count++;
	}

	// ���_�f�[�^���A�����b�N
	this->mVertexBuffer->Unlock();
}

//*****************************************************************************
//
// �C���f�b�N�X���Z�b�g�A�b�v
//
//*****************************************************************************
HRESULT Mesh::setupIndexes()
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// ���_�C���f�b�N�X�o�b�t�@�쐬
	if (FAILED(pD3DDevice->CreateIndexBuffer(this->mIndices.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->mIndexBuffer, NULL)))
	{
		// Debug�E�C���h��
		cout << "<Error> make index buffer ... failed!" << endl;
		return E_FAIL;
	}

	WORD* vertexIndex = nullptr;

	// �C���f�b�N�X �f�[�^�̂�����͈͂����b�N���A���̃C���f�b�N�X�o�b�t�@�������[�ւ̃|�C���^�[���擾
	this->mIndexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);

	unsigned int count = 0;
	for (auto it : this->mIndices)
	{
		vertexIndex[count] = it;

		count++;
	}

	// �C���f�b�N�X �f�[�^�̃��b�N������
	this->mIndexBuffer->Unlock();
}

//*****************************************************************************
//
// ���b�V���̃V���h�E�}�b�v��`��
//
//*****************************************************************************
void Mesh::drawShadow(Shader* shader)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// �`��
	UINT passNum = 0;
	shader->mEffect->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		// �e�p�X��`��
		shader->mEffect->BeginPass(count);

		HRESULT hr;
		// ���_�錾��ݒ�
		hr = pD3DDevice->SetVertexDeclaration(this->mVertexDecl);
		// ���_�o�b�t�@��ݒ�
		hr = pD3DDevice->SetStreamSource(0, this->mVertexBuffer, 0, sizeof(VertexDesign));
		// �C���f�b�N�X�o�b�t�@��ݒ�
		hr = pD3DDevice->SetIndices(this->mIndexBuffer);

		unsigned int vertexNums = mVertices.size();
		unsigned int faceNums = mIndices.size()/3;
		hr = pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNums, 0, faceNums);	// �|���S���̕`��

		shader->mEffect->EndPass();
	}
	shader->mEffect->End();
}

//*****************************************************************************
//
// ���b�V�����h���[
//
//*****************************************************************************
void Mesh::drawModel(Shader* shader)
{
	LPDIRECT3DDEVICE9 pD3DDevice = getD3DDevice();

	// �}�e���A��������n��
	shader->mEffect->SetValue("matAmibent", this->mMaterials.at(0)->mAmbient, sizeof(D3DXVECTOR3));
	shader->mEffect->SetValue("matDiffuse", this->mMaterials.at(0)->mDiffuse, sizeof(D3DXVECTOR3));
	shader->mEffect->SetValue("matSpecular", this->mMaterials.at(0)->mSpecular, sizeof(D3DXVECTOR3));
	shader->mEffect->SetFloat("shininess", this->mMaterials.at(0)->mShininess);

	// �e�N�X�`����n��
	LPDIRECT3DTEXTURE9 tex = this->mMaterials.at(0)->mTextures.at(0)->mTex;
	shader->mEffect->SetTexture("tex", tex);

	// �`��
	UINT passNum = 0;
	shader->mEffect->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		// �e�p�X��`��
		shader->mEffect->BeginPass(count);

		HRESULT hr;
		// ���_�錾��ݒ�
		hr = pD3DDevice->SetVertexDeclaration(this->mVertexDecl);
		// ���_�o�b�t�@��ݒ�
		hr = pD3DDevice->SetStreamSource(0, this->mVertexBuffer, 0, sizeof(VertexDesign));	
		// �C���f�b�N�X�o�b�t�@��ݒ�
		hr = pD3DDevice->SetIndices(this->mIndexBuffer);

		unsigned int vertexNums = mVertices.size();
		unsigned int faceNums = mIndices.size()/3;
		hr = pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNums, 0, faceNums);	// �|���S���̕`��

		shader->mEffect->EndPass();
	}
	shader->mEffect->End();
}

//*****************************************************************************
//
// �o�E���f�B���O�{�b�N�X�T�C�Y�����
//
//*****************************************************************************
void Mesh::createBoundingBox(D3DXVECTOR3 vertexPos, D3DXVECTOR3 &boxMax, D3DXVECTOR3 &boxMin)
{
	if (vertexPos.x > boxMax.x) boxMax.x = vertexPos.x;
	if (vertexPos.x < boxMin.x) boxMin.x = vertexPos.x;
	if (vertexPos.y > boxMax.y) boxMax.y = vertexPos.y;
	if (vertexPos.y < boxMin.y) boxMin.y = vertexPos.y;
	if (vertexPos.z > boxMax.z) boxMax.z = vertexPos.z;
	if (vertexPos.z < boxMin.z) boxMin.z = vertexPos.z;
}